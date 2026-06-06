#!/bin/bash

set -uo pipefail

MINIRT="./build/miniRT"
TEST_DIR="review_files"
LOGFILE="minirt_test_$(date +%Y%m%d_%H%M%S).log"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

log_result() {
    local reqid="$1"
    local status="$2"
    local file="$3"
    local details="$4"
    printf "[%-6s] %-24s %-30s %s\n" "$status" "$reqid" "$(basename "$file")" "$details" >> "$LOGFILE"
}

print_header() {
    local text="$1"
    echo ""
    echo "========================================"
    echo -e "${CYAN}${text}${NC}"
    echo "========================================"
}

check_build() {
    print_header "1. BUILD & EXECUTABLE CHECKS"

    echo ""
    echo -e "${YELLOW}[ReqID: 100001] Verifying compilation...${NC}"
    if [ -f "Makefile" ]; then
        make clean >/dev/null 2>&1 || true
        if make >/dev/null 2>&1; then
            echo -e "${GREEN}OK${NC} - make compiled successfully"
            log_result "100001" "OK" "Makefile" "make compiled successfully"
        else
            echo -e "${RED}FAILED${NC} - make failed"
            log_result "100001" "FAILED" "Makefile" "make compilation failed"
        fi
    else
        echo -e "${RED}FAILED${NC} - Makefile not found"
        log_result "100001" "FAILED" "Makefile" "Makefile not found"
    fi

    echo ""
    echo -e "${YELLOW}[ReqID: 100002] Verifying executable name...${NC}"
    if [ -x "$MINIRT" ]; then
        local basename_exec=$(basename "$MINIRT")
        if [ "$basename_exec" = "miniRT" ]; then
            echo -e "${GREEN}OK${NC} - Executable is named exactly 'miniRT'"
            log_result "100002" "OK" "$MINIRT" "Executable named exactly miniRT"
        else
            echo -e "${RED}FAILED${NC} - Executable is named '$basename_exec'"
            log_result "100002" "FAILED" "$MINIRT" "Executable named $basename_exec instead of miniRT"
        fi
    else
        echo -e "${RED}FAILED${NC} - Executable not found at $MINIRT"
        log_result "100002" "FAILED" "$MINIRT" "Executable not found"
    fi

    echo ""
    read -p "Press Enter to continue to window management tests..."
}

run_window_management_suite() {
    local file="$TEST_DIR/basic_sphere.rt"
    local name=$(basename "$file")
    local tmpout="/tmp/minirt_wm_$$.txt"

    print_header "3. WINDOW & DISPLAY MANAGEMENT"
    echo -e "${BLUE}Using $name for all window management tests${NC}"

    echo ""
    echo -e "${YELLOW}[ReqID: 300001] Launching miniRT to verify window opens...${NC}"
    "$MINIRT" "$file" > "$tmpout" 2>&1 &
    local PID=$!
    sleep 1

    if ! kill -0 $PID 2>/dev/null; then
        wait $PID 2>/dev/null || true
        local EXIT_CODE=$?
        echo -e "${RED}FAILED${NC} - miniRT exited immediately (code: $EXIT_CODE)"
        log_result "300001" "FAILED" "$file" "Process exited immediately, window did not open"
        rm -f "$tmpout"
        read -p "Press Enter to continue..."
        return
    fi

    echo -e "${GREEN}Window is open.${NC}"
    log_result "300001" "OK" "$file" "Window opened and stayed open"

    echo ""
    echo -e "${YELLOW}[ReqID: 300002] Minimize/Maximize/Restore Test${NC}"
    echo -e "${BLUE}Minimize the window, restore it, cover with another window, then uncover.${NC}"
    read -p "Did content remain consistent? (y/n): " answer
    if [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
        echo -e "${GREEN}OK${NC} - Content remained consistent"
        log_result "300002" "OK" "$file" "Content remained consistent after minimize/restore/cover"
    else
        echo -e "${RED}FAILED${NC} - Content was inconsistent or crashed"
        log_result "300002" "FAILED" "$file" "Content inconsistent or crashed"
    fi

    echo ""
    echo -e "${YELLOW}[ReqID: 300003] Window Resolution Change Test${NC}"
    echo -e "${BLUE}Resize the miniRT window (drag corners).${NC}"
    read -p "Did content remain consistent after resizing? (y/n): " answer
    if [ "$answer" = "y" ] || [ "$answer" = "Y" ]; then
        echo -e "${GREEN}OK${NC} - Content remained consistent after resize"
        log_result "300003" "OK" "$file" "Content remained consistent after window resize"
    else
        echo -e "${RED}FAILED${NC} - Content was inconsistent or crashed after resize"
        log_result "300003" "FAILED" "$file" "Content inconsistent or crashed after resize"
    fi

    kill $PID 2>/dev/null || true
    wait $PID 2>/dev/null || true
    sleep 0.5

    echo ""
    echo -e "${YELLOW}[ReqID: 300004] ESC Key Exit Test${NC}"
    echo -e "${BLUE}Reopening window. Press ESC to close it.${NC}"
    "$MINIRT" "$file" > "$tmpout" 2>&1 &
    PID=$!
    sleep 1

    if ! kill -0 $PID 2>/dev/null; then
        echo -e "${RED}FAILED${NC} - Window closed immediately"
        log_result "300004" "FAILED" "$file" "Window closed immediately, could not test ESC"
    else
        echo -e "${GREEN}Window is open.${NC} Press ESC in miniRT window, then press Enter here."
        read -p ""

        if ! kill -0 $PID 2>/dev/null; then
            wait $PID 2>/dev/null || true
            local EXIT_CODE=$?
            if [ $EXIT_CODE -eq 0 ]; then
                echo -e "${GREEN}OK${NC} - Program exited cleanly (code: 0) after ESC"
                log_result "300004" "OK" "$file" "ESC exited cleanly (code: 0)"
            else
                echo -e "${RED}FAILED${NC} - Program exited with code $EXIT_CODE after ESC"
                log_result "300004" "FAILED" "$file" "ESC exited with code $EXIT_CODE (expected 0)"
            fi
        else
            echo -e "${YELLOW}Window still open.${NC} Did you press ESC? Press Enter to force close."
            read -p ""
            kill $PID 2>/dev/null || true
            wait $PID 2>/dev/null || true
            log_result "300004" "FAILED" "$file" "ESC did not close window"
        fi
    fi

    rm -f "$tmpout"
    sleep 0.5

    echo ""
    echo -e "${YELLOW}[ReqID: 300005] Red Cross Exit Test${NC}"
    echo -e "${BLUE}Reopening window. Click the red cross / close button.${NC}"
    "$MINIRT" "$file" > "$tmpout" 2>&1 &
    PID=$!
    sleep 1

    if ! kill -0 $PID 2>/dev/null; then
        echo -e "${RED}FAILED${NC} - Window closed immediately"
        log_result "300005" "FAILED" "$file" "Window closed immediately, could not test red cross"
    else
        echo -e "${GREEN}Window is open.${NC} Click the close button, then press Enter here."
        read -p ""

        if ! kill -0 $PID 2>/dev/null; then
            wait $PID 2>/dev/null || true
            local EXIT_CODE=$?
            if [ $EXIT_CODE -eq 0 ]; then
                echo -e "${GREEN}OK${NC} - Program exited cleanly (code: 0) after red cross"
                log_result "300005" "OK" "$file" "Red cross exited cleanly (code: 0)"
            else
                echo -e "${RED}FAILED${NC} - Program exited with code $EXIT_CODE after red cross"
                log_result "300005" "FAILED" "$file" "Red cross exited with code $EXIT_CODE (expected 0)"
            fi
        else
            echo -e "${YELLOW}Window still open.${NC} Did you click the close button? Press Enter to force close."
            read -p ""
            kill $PID 2>/dev/null || true
            wait $PID 2>/dev/null || true
            log_result "300005" "FAILED" "$file" "Red cross did not close window"
        fi
    fi

    rm -f "$tmpout"
    echo ""
    read -p "Press Enter to continue to scene rendering tests..."
}

run_visual_test() {
    local file="$1"
    local reqid="$2"
    local description="$3"
    local name=$(basename "$file")
    local tmpout="/tmp/minirt_viz_$$_${name}.txt"

    echo ""
    echo "========================================"
    echo -e "${YELLOW}[ReqID: ${reqid}] ${description}${NC}"
    echo -e "${BLUE}File: ${name}${NC}"
    echo ""

    "$MINIRT" "$file" > "$tmpout" 2>&1 &
    local PID=$!
    sleep 1

    if ! kill -0 $PID 2>/dev/null; then
        wait $PID 2>/dev/null || true
        local EXIT_CODE=$?
        echo -e "${RED}FAILED${NC} - miniRT exited immediately (code: $EXIT_CODE), window did not open"
        log_result "$reqid" "FAILED" "$file" "Process exited immediately (code: $EXIT_CODE)"
        echo ""
        read -p "Press Enter to continue..."
        rm -f "$tmpout"
        return
    fi

    echo -e "${GREEN}Window is open.${NC} Please verify the render visually."
    echo -e "${BLUE}Press Enter when ready to continue...${NC}"
    read -p ""

    if kill -0 $PID 2>/dev/null; then
        kill $PID 2>/dev/null || true
        wait $PID 2>/dev/null || true
        local EXIT_CODE=$?
        if [ $EXIT_CODE -eq 0 ] || [ $EXIT_CODE -eq 143 ]; then
            echo -e "${GREEN}OK${NC} - User verified render, window closed cleanly"
            log_result "$reqid" "OK" "$file" "Window opened, user verified render, closed cleanly"
        else
            echo -e "${RED}FAILED${NC} - Window closed with unexpected code: $EXIT_CODE"
            log_result "$reqid" "FAILED" "$file" "Unexpected exit code: $EXIT_CODE"
        fi
    else
        wait $PID 2>/dev/null || true
        local EXIT_CODE=$?
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "${GREEN}OK${NC} - User closed window cleanly (exit code: 0)"
            log_result "$reqid" "OK" "$file" "Window opened, user closed cleanly (code: 0)"
        else
            echo -e "${RED}FAILED${NC} - Window closed with code: $EXIT_CODE"
            log_result "$reqid" "FAILED" "$file" "Window closed with code: $EXIT_CODE"
        fi
    fi

    if [ -s "$tmpout" ]; then
        echo -e "${YELLOW}Note: Unexpected output from miniRT:${NC}"
        cat "$tmpout"
    fi

    rm -f "$tmpout"
}

run_misconfig_test() {
    local file="$1"
    local reqids="$2"
    local description="$3"
    local name=$(basename "$file")
    local tmpout="/tmp/minirt_err_$$_${name}.txt"

    echo ""
    echo "========================================"
    echo -e "${YELLOW}[ReqID: ${reqids}] ${description}${NC}"
    echo -e "${BLUE}File: ${name}${NC}"
    echo ""

    local EXIT_CODE=0
    "$MINIRT" "$file" > "$tmpout" 2>&1 || EXIT_CODE=$?

    echo "Exit code: $EXIT_CODE"

    if [ $EXIT_CODE -eq 2 ]; then
        echo -e "${GREEN}FAILED AS EXPECTED${NC} - Error detected, exit code 2, no window opened"
        log_result "$reqids" "FAILED_AS_EXPECTED" "$file" "Exit code 2 - error message printed, no window"
        if [ -s "$tmpout" ]; then
            echo "Error output:"
            cat "$tmpout"
        fi
    elif [ $EXIT_CODE -eq 0 ]; then
        echo -e "${RED}FAILED${NC} - Program exited cleanly (code: 0) but should have failed"
        log_result "$reqids" "FAILED" "$file" "Exit code 0 - should have returned error"
        if [ -s "$tmpout" ]; then
            echo "Output:"
            cat "$tmpout"
        fi
    else
        echo -e "${RED}FAILED${NC} - Unexpected exit code: $EXIT_CODE (expected 2)"
        log_result "$reqids" "FAILED" "$file" "Unexpected exit code: $EXIT_CODE (expected 2)"
        if [ -s "$tmpout" ]; then
            echo "Output:"
            cat "$tmpout"
        fi
    fi

    rm -f "$tmpout"
    read -p "Press Enter to continue..."
}

echo "========================================"
echo "     miniRT Visual Test Runner"
echo "     Requirement ID Tracing Enabled"
echo "========================================"
echo ""
echo "Results are logged to: $LOGFILE"
echo ""

echo "miniRT Visual Test Session - $(date '+%Y-%m-%d %H:%M:%S')" > "$LOGFILE"
echo "Executable: $MINIRT" >> "$LOGFILE"
echo "Test Directory: $TEST_DIR" >> "$LOGFILE"
echo "========================================" >> "$LOGFILE"
printf "%-8s %-24s %-30s %s\n" "STATUS" "REQ_ID" "FILE" "DETAILS" >> "$LOGFILE"
echo "----------------------------------------" >> "$LOGFILE"

read -p "Press Enter to start testing..."

check_build
run_window_management_suite

echo ""
print_header "4. BASIC SHAPES RENDERING"
run_visual_test "$TEST_DIR/basic_sphere.rt" "400001" "Sphere at {0,0,0} with camera facing it"
run_visual_test "$TEST_DIR/basic_plane.rt" "400002" "Plane placed with z = 0, camera facing it"
run_visual_test "$TEST_DIR/basic_cylinder.rt" "400003" "Cylinder extending along Y axis, camera facing it"

echo ""
print_header "5. TRANSFORMATIONS (Translation & Rotation)"
run_visual_test "$TEST_DIR/translation_test.rt" "500001" "Two spheres at {0,0,0}, one translated parallel to camera"
run_visual_test "$TEST_DIR/rotation_test.rt" "500002" "Cylinder along Y axis rotated 90 degrees around Z axis"

echo ""
print_header "6. MULTI-OBJECT SCENES"
run_visual_test "$TEST_DIR/intersecting_objects.rt" "600001" "Intersecting sphere and cylinder"
run_visual_test "$TEST_DIR/duplicate_objects.rt" "600002" "Two cylinders, two spheres, one plane"

echo ""
print_header "7. CAMERA POSITION & ORIENTATION"
run_visual_test "$TEST_DIR/camera_x_axis.rt" "700001" "Camera along X axis, pointed at {0,0,0}"
run_visual_test "$TEST_DIR/camera_y_axis.rt" "700002" "Camera along Y axis, pointed at {0,0,0}"
run_visual_test "$TEST_DIR/camera_z_axis.rt" "700003" "Camera along Z axis, pointed at {0,0,0}"
run_visual_test "$TEST_DIR/camera_random.rt" "700004" "Camera at random off-axis location, pointed at {0,0,0}"

echo ""
print_header "8. LIGHTING & BRIGHTNESS"
run_visual_test "$TEST_DIR/lighting_sideways.rt" "800001" "Sphere at {0,0,0} lit sideways by spot light"
run_visual_test "$TEST_DIR/lighting_translated.rt" "800002" "Translated sphere lit sideways (halo after translation)"

echo ""
print_header "9. SHADOWS"
run_visual_test "$TEST_DIR/shadow_simple.rt" "900001" "Sphere casting shadow on plane with vertical spot"
run_visual_test "$TEST_DIR/shadow_complex.rt" "900002" "Complex multi-object scene with shadows"

echo ""
print_header "2. CONFIGURATION FILE PARSING - MISCONFIGURATION (.rt files)"
for file in "$TEST_DIR"/misconfig_rt_*.rt; do
    [ -e "$file" ] || continue
    run_misconfig_test "$file" "200002" "Misconfigured content in .rt file"
done

echo ""
print_header "2. CONFIGURATION FILE PARSING - WRONG EXTENSION (.txt files)"
for file in "$TEST_DIR"/misconfig_txt_*.txt; do
    [ -e "$file" ] || continue
    run_misconfig_test "$file" "200003,200002" "Wrong extension (.txt) + misconfigured content"
done

echo ""
print_header "TESTING COMPLETE"
echo "Log file: $LOGFILE"
echo ""

OK_COUNT=$(grep -c "OK" "$LOGFILE" 2>/dev/null || echo 0)
EXP_FAIL_COUNT=$(grep -c "FAILED_AS_EXPECTED" "$LOGFILE" 2>/dev/null || echo 0)
FAIL_COUNT=$(grep -c "FAILED" "$LOGFILE" 2>/dev/null || echo 0)

echo -e "${GREEN}OK: $OK_COUNT${NC}"
echo -e "${GREEN}FAILED AS EXPECTED: $EXP_FAIL_COUNT${NC}"
echo -e "${RED}FAILED: $FAIL_COUNT${NC}"
echo ""
echo "Full log contents:"
echo "----------------------------------------"
cat "$LOGFILE"
echo "----------------------------------------"
