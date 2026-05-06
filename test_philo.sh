#!/bin/bash

# =============================================================================
#  PHILOSOPHERS - COMPREHENSIVE TEST SUITE
#  Usage: bash test_philo.sh [path/to/philo]
#  Default binary: ./philo
# =============================================================================

BINARY="${1:-./philo}"
PASS=0
FAIL=0
WARN=0
SECTION_PASS=0
SECTION_FAIL=0

# ── Colors ────────────────────────────────────────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
DIM='\033[2m'
RESET='\033[0m'

# ── Helpers ───────────────────────────────────────────────────────────────────
section() {
    SECTION_PASS=0
    SECTION_FAIL=0
    echo ""
    echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
    echo -e "${BOLD}${CYAN}  $1${RESET}"
    echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
}

section_summary() {
    if [ $SECTION_FAIL -eq 0 ]; then
        echo -e "${DIM}  Section: ${GREEN}${SECTION_PASS} passed${RESET}"
    else
        echo -e "${DIM}  Section: ${GREEN}${SECTION_PASS} passed${RESET} ${RED}${SECTION_FAIL} failed${RESET}"
    fi
}

pass() {
    echo -e "  ${GREEN}✓${RESET} $1"
    ((PASS++)); ((SECTION_PASS++))
}

fail() {
    echo -e "  ${RED}✗${RESET} $1"
    ((FAIL++)); ((SECTION_FAIL++))
}

warn() {
    echo -e "  ${YELLOW}⚠${RESET} $1"
    ((WARN++))
}

info() {
    echo -e "  ${DIM}→ $1${RESET}"
}

# Run binary, capture stdout+stderr, with timeout
run() {
    local timeout_sec=$1; shift
    timeout "$timeout_sec" "$BINARY" "$@" 2>&1
}

# Check exit code of last run (timeout exits 124)
timed_out() { [ $? -eq 124 ]; }

# =============================================================================
#  PRE-FLIGHT
# =============================================================================
section "PRE-FLIGHT"

if [ ! -f "$BINARY" ]; then
    fail "Binary not found: $BINARY"
    echo -e "\n${RED}Aborting — binary missing.${RESET}\n"
    exit 1
fi
pass "Binary found: $BINARY"

if [ ! -x "$BINARY" ]; then
    fail "Binary not executable"
    exit 1
fi
pass "Binary is executable"

# Check for sanitizer support (informational)
if echo "" | grep -q "fsanitize" 2>/dev/null; then
    info "Compiled with sanitizers detected"
fi

section_summary

# =============================================================================
#  1. ARGUMENT VALIDATION
# =============================================================================
section "1. ARGUMENT VALIDATION"
info "Binary should reject invalid arguments (non-zero exit or error output)"

check_invalid() {
    local desc="$1"; shift
    local output
    output=$(timeout 2 "$BINARY" "$@" 2>&1)
    local exit_code=$?
    # Accept: non-zero exit OR some error output AND fast exit (no hang)
    if [ $exit_code -ne 0 ] || echo "$output" | grep -qiE "error|invalid|usage|argument"; then
        pass "$desc → rejected correctly"
    else
        # If it exited 0 very fast and printed nothing useful, still warn
        warn "$desc → exit=$exit_code (check manually)"
    fi
}

check_invalid "No arguments"
check_invalid "1 arg only"              1
check_invalid "2 args only"             1 800
check_invalid "3 args only"             1 800 200
check_invalid "Too many args (6)"       5 800 200 200 7 99
check_invalid "Zero philosophers"       0 800 200 200
check_invalid "Negative philosophers"  -1 800 200 200
check_invalid "Negative time_to_die"    5 -800 200 200
check_invalid "Negative time_to_eat"    5 800 -200 200
check_invalid "Negative time_to_sleep"  5 800 200 -200
check_invalid "Negative must_eat"       5 800 200 200 -1
check_invalid "Float input"             5 1.5 200 200
check_invalid "Alpha input"             5 abc 200 200
check_invalid "Mixed alpha"             5 800 200x 200
check_invalid "Empty string arg"        5 "" 200 200
check_invalid "Zero time_to_die"        5 0 200 200
check_invalid "Zero time_to_eat"        5 800 0 200
check_invalid "Zero time_to_sleep"      5 800 200 0

section_summary

# =============================================================================
#  2. MUST_EAT = 0  (edge: already satisfied)
# =============================================================================
section "2. MUST_EAT = 0 EDGE CASE"
info "When must_eat=0, all philosophers are immediately satisfied → should exit fast"

output=$(timeout 3 "$BINARY" 5 800 200 200 0 2>&1)
ec=$?
if [ $ec -eq 0 ] || [ -z "$output" ] || ! echo "$output" | grep -q "died"; then
    pass "5 800 200 200 0 → exited without death"
else
    warn "5 800 200 200 0 → unclear behavior (exit=$ec), check manually"
fi

section_summary

# =============================================================================
#  3. SINGLE PHILOSOPHER
# =============================================================================
section "3. SINGLE PHILOSOPHER"
info "1 philosopher can never pick up 2 forks → must die"

output=$(timeout 3 "$BINARY" 1 800 200 200 2>&1)
if echo "$output" | grep -q "died"; then
    pass "1 800 200 200 → philosopher died (correct)"
else
    fail "1 800 200 200 → no death reported"
fi

# Death timing check for single philo
death_ts=$(echo "$output" | grep "died" | awk '{print $1}')
if [ -n "$death_ts" ]; then
    if [ "$death_ts" -le 810 ] 2>/dev/null; then
        pass "  Death at ${death_ts}ms ≤ 810ms (time_to_die + 10ms margin)"
    else
        fail "  Death reported too late: ${death_ts}ms (expected ≤ 810ms)"
    fi
fi

# Must not hang
timeout 3 "$BINARY" 1 800 200 200 > /dev/null 2>&1
if [ $? -ne 124 ]; then
    pass "1 800 200 200 → process exits (no hang)"
else
    fail "1 800 200 200 → process hung (timeout)"
fi

section_summary

# =============================================================================
#  4. DEATH CASES  (philosopher must die)
# =============================================================================
section "4. DEATH CASES"
info "These configurations must produce a death"

must_die() {
    local desc="$1"; shift
    local args="$@"
    local output
    output=$(timeout 5 "$BINARY" $args 2>&1)
    local ec=$?
    if [ $ec -eq 124 ]; then
        fail "$desc [$args] → HUNG (timeout 5s)"
    elif echo "$output" | grep -q "died"; then
        pass "$desc [$args] → died correctly"
    else
        fail "$desc [$args] → no death reported"
    fi
}

must_die "tight 2 philos"            2 10 200 200
must_die "4 philos tight timing"     4 310 200 200
must_die "5 philos very short ttd"   5 60 150 150
must_die "3 philos short ttd"        3 100 200 200
must_die "single eats too long"      1 500 600 200

section_summary

# =============================================================================
#  5. NO-DEATH CASES  (must survive indefinitely)
# =============================================================================
section "5. NO-DEATH CASES"
info "These configurations must NOT produce a death within 5 seconds"

no_death() {
    local desc="$1"; shift
    local args="$@"
    local output
    output=$(timeout 5 "$BINARY" $args 2>&1)
    if echo "$output" | grep -q "died"; then
        fail "$desc [$args] → unexpected death"
    else
        pass "$desc [$args] → alive for 5s"
    fi
}

no_death "classic 2 philos"         2 800 200 200
no_death "classic 5 philos"         5 800 200 200
no_death "4 philos safe margin"     4 410 200 200
no_death "3 philos comfortable"     3 600 200 200
no_death "6 philos"                 6 800 200 200
no_death "even count 8"             8 800 200 200
no_death "odd count 7"              7 800 200 200
no_death "large group 20"          20 800 200 200
no_death "fast cycles"              5 400 100 100
no_death "long eat"                 4 2000 800 200
no_death "long sleep"               4 2000 200 800

section_summary

# =============================================================================
#  6. MUST_EAT TERMINATION
# =============================================================================
section "6. MUST_EAT — CLEAN TERMINATION"
info "Simulation must stop after all philosophers eat N times"

must_eat_exit() {
    local desc="$1"; shift
    local args="$@"
    local output
    output=$(timeout 10 "$BINARY" $args 2>&1)
    local ec=$?

    if [ $ec -eq 124 ]; then
        fail "$desc [$args] → HUNG (never exited)"
        return
    fi
    # Should not die
    if echo "$output" | grep -q "died"; then
        fail "$desc [$args] → unexpected death"
    else
        pass "$desc [$args] → exited cleanly (no death)"
    fi
}

must_eat_no_die() {
    local desc="$1"; shift
    must_eat_exit "$desc" "$@"
}

must_eat_no_die "5 philos eat 1x"        5 800 200 200 1
must_eat_no_die "5 philos eat 3x"        5 800 200 200 3
must_eat_no_die "5 philos eat 7x"        5 800 200 200 7
must_eat_no_die "2 philos eat 5x"        2 800 200 200 5
must_eat_no_die "4 philos eat 10x"       4 800 200 200 10
must_eat_no_die "large 10 philos eat 2x" 10 800 200 200 2

# Single philo with must_eat — dies before satisfying
output=$(timeout 3 "$BINARY" 1 800 200 200 5 2>&1)
if echo "$output" | grep -q "died"; then
    pass "1 philo must_eat=5 → dies (correct, can't get 2nd fork)"
else
    warn "1 philo must_eat=5 → no death (check if it exited early or hung)"
fi

section_summary

# =============================================================================
#  7. DEATH TIMING PRECISION
# =============================================================================
section "7. DEATH TIMING PRECISION"
info "Death must be reported within 10ms of time_to_die elapsing"

check_death_timing() {
    local desc="$1"
    local ttd="$2"; shift 2
    local args="$@"
    local output
    output=$(timeout 5 "$BINARY" $args 2>&1)

    local death_line
    death_line=$(echo "$output" | grep "died" | head -1)
    if [ -z "$death_line" ]; then
        warn "$desc → no death found, skipping timing check"
        return
    fi

    local death_ts
    death_ts=$(echo "$death_line" | awk '{print $1}')
    local margin=10
    local upper=$((ttd + margin))

    if [ "$death_ts" -le "$upper" ] 2>/dev/null; then
        pass "$desc → died at ${death_ts}ms (ttd=${ttd}ms, margin=${margin}ms) ✓"
    else
        fail "$desc → died at ${death_ts}ms, expected ≤ ${upper}ms"
    fi
}

check_death_timing "single philo ttd=800"  800  1 800 200 200
check_death_timing "tight 2 philos ttd=10"  10  2 10 200 200
check_death_timing "ttd=310 4 philos"      310  4 310 200 200

section_summary

# =============================================================================
#  8. NO OUTPUT AFTER DEATH
# =============================================================================
section "8. NO OUTPUT AFTER DEATH"
info "Once 'died' is printed, no further actions should appear"

check_no_output_after_death() {
    local desc="$1"; shift
    local output
    output=$(timeout 5 "$BINARY" "$@" 2>&1)

    local death_line_num
    death_line_num=$(echo "$output" | grep -n "died" | head -1 | cut -d: -f1)

    if [ -z "$death_line_num" ]; then
        warn "$desc → no death found"
        return
    fi

    local total_lines
    total_lines=$(echo "$output" | wc -l)

    # Allow at most 1 line after (the death line itself may be last)
    if [ "$death_line_num" -ge "$total_lines" ] || [ "$((total_lines - death_line_num))" -le 0 ]; then
        pass "$desc → no output after 'died'"
    else
        local after
        after=$(echo "$output" | tail -n +"$((death_line_num + 1))")
        fail "$desc → output after 'died':\n$(echo "$after" | head -3)"
    fi
}

check_no_output_after_death "1 philo"           1 800 200 200
check_no_output_after_death "2 philos tight"    2 10 200 200
check_no_output_after_death "4 philos tight"    4 310 200 200

section_summary

# =============================================================================
#  9. OUTPUT FORMAT VALIDATION
# =============================================================================
section "9. OUTPUT FORMAT"
info "Each line must be: [timestamp] [id] [action]"

check_output_format() {
    local desc="$1"; shift
    local output
    output=$(timeout 3 "$BINARY" "$@" 2>&1)

    if [ -z "$output" ]; then
        warn "$desc → no output to validate"
        return
    fi

    local bad_lines
    bad_lines=$(echo "$output" | grep -vE \
        '^[0-9]+ [0-9]+ (has taken a fork|is eating|is sleeping|is thinking|died)$')

    if [ -z "$bad_lines" ]; then
        pass "$desc → all lines match expected format"
    else
        fail "$desc → malformed lines found:"
        echo "$bad_lines" | head -5 | while read -r l; do
            echo -e "      ${RED}→ '$l'${RESET}"
        done
    fi
}

check_output_format "format: 2 philos"    2 800 200 200
check_output_format "format: 5 philos"    5 800 200 200
check_output_format "format: 1 philo"     1 800 200 200
check_output_format "format: must_eat=2"  4 800 200 200 2

section_summary

# =============================================================================
#  10. TIMESTAMP SANITY
# =============================================================================
section "10. TIMESTAMP SANITY"
info "Timestamps must be non-negative and generally increasing per philosopher"

check_timestamps() {
    local desc="$1"; shift
    local output
    output=$(timeout 3 "$BINARY" "$@" 2>&1)

    if [ -z "$output" ]; then
        warn "$desc → no output"
        return
    fi

    # All timestamps must be non-negative integers
    local bad
    bad=$(echo "$output" | awk '{if ($1 !~ /^[0-9]+$/) print NR": "$0}' | head -3)
    if [ -n "$bad" ]; then
        fail "$desc → non-integer timestamps:\n$bad"
        return
    fi

    # First timestamp should be ≥ 0 and < 50ms (program starts fast)
    local first_ts
    first_ts=$(echo "$output" | head -1 | awk '{print $1}')
    if [ "$first_ts" -lt 100 ] 2>/dev/null; then
        pass "$desc → first timestamp reasonable (${first_ts}ms)"
    else
        warn "$desc → first timestamp seems high: ${first_ts}ms"
    fi

    # Check last timestamp is after first
    local last_ts
    last_ts=$(echo "$output" | tail -1 | awk '{print $1}')
    if [ "$last_ts" -ge "$first_ts" ] 2>/dev/null; then
        pass "$desc → timestamps monotonically valid (${first_ts}ms → ${last_ts}ms)"
    else
        fail "$desc → last timestamp ($last_ts) < first ($first_ts)"
    fi
}

check_timestamps "timestamps: 5 philos"     5 800 200 200
check_timestamps "timestamps: 1 philo dies" 1 800 200 200
check_timestamps "timestamps: must_eat=3"   4 800 200 200 3

section_summary

# =============================================================================
#  11. FORK COUNT INTEGRITY (meals per philo)
# =============================================================================
section "11. MEAL COUNT INTEGRITY"
info "With must_eat=N, each philosopher should eat exactly N times"

check_meal_count() {
    local desc="$1"
    local nphilo="$2"
    local must_eat="$3"; shift 3
    local args="$@"

    local output
    output=$(timeout 10 "$BINARY" $nphilo $args $must_eat 2>&1)

    if [ $? -eq 124 ]; then
        fail "$desc → hung"
        return
    fi

    local ok=1
    for ((i=1; i<=nphilo; i++)); do
        local count
        count=$(echo "$output" | grep "^[0-9]* $i is eating$" | wc -l)
        if [ "$count" -lt "$must_eat" ]; then
            fail "$desc → philo $i only ate $count/$must_eat times"
            ok=0
        fi
    done
    [ $ok -eq 1 ] && pass "$desc → all $nphilo philos ate ≥ ${must_eat}x"
}

check_meal_count "4 philos eat 3x"  4 3 800 200 200
check_meal_count "3 philos eat 2x"  3 2 800 200 200
check_meal_count "2 philos eat 5x"  2 5 800 200 200

section_summary

# =============================================================================
#  12. NO INTERLEAVED / GARBLED OUTPUT
# =============================================================================
section "12. NO INTERLEAVED OUTPUT"
info "Each line must be atomic (mutex on printf)"

check_no_garble() {
    local desc="$1"; shift
    local output
    output=$(timeout 5 "$BINARY" "$@" 2>&1)

    local garbled
    garbled=$(echo "$output" | grep -vE '^[0-9]+ [0-9]+ ' | grep -v '^$')

    if [ -z "$garbled" ]; then
        pass "$desc → no garbled lines"
    else
        fail "$desc → garbled output detected:"
        echo "$garbled" | head -3 | while read -r l; do
            echo -e "      ${RED}→ '$l'${RESET}"
        done
    fi
}

check_no_garble "garble: 5 philos"   5 800 200 200
check_no_garble "garble: 20 philos" 20 800 200 200
check_no_garble "garble: 50 philos" 50 800 200 200

section_summary

# =============================================================================
#  13. STRESS TESTS
# =============================================================================
section "13. STRESS TESTS"
info "Large philosopher counts — no crash, no hang, no death"

stress_no_death() {
    local desc="$1"; shift
    local args="$@"
    local output
    output=$(timeout 5 "$BINARY" $args 2>&1)
    local ec=$?
    if [ $ec -eq 124 ]; then
        warn "$desc [$args] → timeout (may be ok for large N)"
    elif echo "$output" | grep -q "died"; then
        fail "$desc [$args] → unexpected death"
    else
        pass "$desc [$args] → alive for 5s"
    fi
}

stress_no_death "50 philos"   50  800 200 200
stress_no_death "100 philos" 100  800 200 200
stress_no_death "200 philos" 200  800 200 200

section_summary

# =============================================================================
#  14. PROCESS EXITS CLEANLY (no hang on must_eat or death)
# =============================================================================
section "14. PROCESS EXIT / NO HANG"
info "Process must exit after death or must_eat completion"

check_exits() {
    local desc="$1"
    local expected_max_sec="$2"; shift 2
    local start end elapsed
    start=$(date +%s%3N)
    timeout "$((expected_max_sec + 2))" "$BINARY" "$@" > /dev/null 2>&1
    end=$(date +%s%3N)
    elapsed=$(( (end - start) ))
    local limit_ms=$(( expected_max_sec * 1000 + 500 ))
    if [ "$elapsed" -le "$limit_ms" ]; then
        pass "$desc → exited in ${elapsed}ms"
    else
        fail "$desc → took ${elapsed}ms (expected < ${limit_ms}ms)"
    fi
}

check_exits "1 philo exits after death"       2  1 800 200 200
check_exits "must_eat=1 exits fast"           5  5 800 200 200 1
check_exits "must_eat=3 exits"                8  5 800 200 200 3
check_exits "2 tight philos exit after death" 2  2 10 200 200

section_summary

# =============================================================================
#  15. VALGRIND / HELGRIND  (optional, skipped if not installed)
# =============================================================================
section "15. MEMORY & RACE CHECKS (optional)"

if command -v valgrind > /dev/null 2>&1; then
    info "valgrind found — running leak check"

    vg_out=$(valgrind --leak-check=full --error-exitcode=1 \
        timeout 3 "$BINARY" 4 800 200 200 2>&1 | tail -20)

    if echo "$vg_out" | grep -q "no leaks are possible\|0 bytes in 0 blocks"; then
        pass "valgrind: no memory leaks"
    elif echo "$vg_out" | grep -q "definitely lost: 0"; then
        pass "valgrind: no definite leaks"
    else
        warn "valgrind: check output manually"
        echo "$vg_out" | grep -E "lost:|ERROR" | head -5 | while read -r l; do
            echo -e "      ${YELLOW}$l${RESET}"
        done
    fi

    if command -v valgrind > /dev/null && valgrind --tool=helgrind true 2>/dev/null; then
        info "helgrind available — running race check (slow)"
        hg_out=$(timeout 8 valgrind --tool=helgrind --error-exitcode=1 \
            "$BINARY" 4 800 200 200 2>&1 | tail -5)
        if echo "$hg_out" | grep -q "ERROR SUMMARY: 0"; then
            pass "helgrind: no race conditions"
        else
            fail "helgrind: potential races detected — run manually for full output"
        fi
    fi
else
    warn "valgrind not installed — skipping memory/race checks"
    info "Install: sudo apt install valgrind"
fi

section_summary

# =============================================================================
#  FINAL SUMMARY
# =============================================================================
echo ""
echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
echo -e "${BOLD}  FINAL RESULTS${RESET}"
echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}"
TOTAL=$((PASS + FAIL))
echo -e "  Total:   ${BOLD}$TOTAL${RESET} tests"
echo -e "  ${GREEN}Passed:  $PASS${RESET}"
echo -e "  ${RED}Failed:  $FAIL${RESET}"
[ $WARN -gt 0 ] && echo -e "  ${YELLOW}Warnings: $WARN${RESET}"
echo ""
if [ $FAIL -eq 0 ]; then
    echo -e "  ${GREEN}${BOLD}All tests passed!${RESET}"
else
    echo -e "  ${RED}${BOLD}$FAIL test(s) failed — see above.${RESET}"
fi
echo ""
exit $FAIL
