
op through tests 1 to 9
for i in {1..10}; do
    echo "Running test t$i..."

    # Run the command for each test
    ./hw1 < t$i.in 2>&1 > t$i.res

    # Compare the result with the expected output
    diff t$i.res t$i.out > diff_t$i.log

    # Check if the diff is empty
    if [ $? -eq 0 ]; then
        echo "Test t$i: Passed"
    else
        echo "Test t$i: Failed. See diff_t$i.log for details."
    fi
done

