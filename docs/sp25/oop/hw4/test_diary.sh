#!/bin/bash

declare -a failed_tests

# Backup the original diary.txt
cp diary.txt diary.txt.bak

restore_diary() {
    cp diary.txt.bak diary.txt >/dev/null 2>&1
}

check_result() {
    local test_num="$1"
    local test_name="$2"
    local condition="$3"
    
    echo -n "Test ${test_num}: ${test_name}... " >/dev/tty
    
    if eval "$condition" >/dev/null 2>&1; then
        echo "✅ Success" >/dev/tty
    else
        echo "❌ Failed" >/dev/tty
        failed_tests+=("Test ${test_num}")
    fi
}

exec >/dev/null 2>&1

# ===== pdadd =====
echo "===== Testing pdadd =====" >/dev/tty
restore_diary

echo "Test 1: Adding new entry 4.1" >/dev/tty
./program/pdadd.exe <<EOF
pdadd 4.1
Sunny today!
Happy April Fools Day!
.
bye
EOF
check_result "1" "Add new entry" 'grep -q "4.1" diary.txt && grep -A1 "4.1" diary.txt | grep -q "Sunny today!"'

restore_diary
echo "Test 2: Adding empty content" >/dev/tty
./program/pdadd.exe <<EOF
pdadd 4.2
.
EOF
check_result "2" "Handle empty content" '! grep -q "4.2" diary.txt'

restore_diary
echo "Test 3: Replacing existing entry" >/dev/tty
./program/pdadd.exe <<EOF
pdadd 4.4
Wish you peace and health during the QingMing Festival!
EOF
check_result "3" "Replace existing entry" 'grep -A1 "4.4" diary.txt | grep -q "Wish you peace and health during the QingMing Festival!"'

# ===== pdlist =====
echo -e "\n===== Testing pdlist =====" >/dev/tty
restore_diary

echo "Test 4: List all entries" >/dev/tty
./program/pdlist.exe <<EOF > pdlist_all.txt
pdlist
bye
EOF
check_result "4" "List all entries" 'grep -q "1.1" pdlist_all.txt && grep -q "10.1" pdlist_all.txt'

echo "Test 5: List date range" >/dev/tty
./program/pdlist.exe <<EOF > pdlist_range.txt
pdlist [4.1,6.1]
bye
EOF
check_result "5" "Date range query" 'grep -q "4.4" pdlist_range.txt && grep -q "5.1" pdlist_range.txt && ! grep -q "10.1" pdlist_range.txt'

# ===== pdshow =====
echo -e "\n===== Testing pdshow =====" >/dev/tty
restore_diary

echo "Test 6: Show existing entry" >/dev/tty
./program/pdshow.exe <<EOF > pdshow.txt
pdshow 10.1
bye
EOF
check_result "6" "Show existing entry" 'grep -q "National Day" pdshow.txt'

echo "Test 7: Show non-existent entry" >/dev/tty
./program/pdshow.exe <<EOF > pdshow_fail.txt
pdshow 10.2
bye
EOF
check_result "7" "Handle missing entry" 'grep -q "Contents Not Found" pdshow_fail.txt'

# ===== pdremove =====
echo -e "\n===== Testing pdremove =====" >/dev/tty
restore_diary

echo "Test 8: Remove existing entry" >/dev/tty
./program/pdremove.exe <<EOF
pdremove 1.1
bye
EOF
check_result "8" "Remove existing entry" '! grep -q "1.1" diary.txt'

restore_diary
echo "Test 9: Remove non-existent entry" >/dev/tty
./program/pdremove.exe <<EOF > pdremove_fail.txt
pdremove 1.2
bye
EOF
check_result "9" "Handle invalid removal" 'grep -q "remove fail" pdremove_fail.txt'

exec >/dev/tty
restore_diary
rm -f diary.txt.bak pdlist_all.txt pdlist_range.txt pdshow.txt pdshow_fail.txt pdremove_fail.txt

echo -e "\n===== Test Results ====="
if [ ${#failed_tests[@]} -eq 0 ]; then
    echo "✅ All 9 tests passed successfully!"
else
    echo "❌ Failed tests (${#failed_tests[@]}/9):"
    printf ' • %s\n' "${failed_tests[@]}"
fi

exit ${#failed_tests[@]}