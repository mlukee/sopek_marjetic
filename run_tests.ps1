# Change to the directory where the executable and test cases are located
Set-Location -Path "C:\Users\Asus\Desktop\sopek_marjetic"

# List of test case numbers to run
$testCaseNumbers = 1..13 | Where-Object { $_ -ne 7 -and $_ -ne 11 }

foreach ($num in $testCaseNumbers) {
    $formattedNumber = "{0:D2}" -f $num
    $inputFile = ".\test_cases\marjetice$formattedNumber.in"
    $outputFile = ".\out.txt"
    $expectedOutputFile = ".\test_cases\marjetice$formattedNumber.out"

    # Clear existing output file
    if (Test-Path $outputFile) {
        Remove-Item $outputFile
    }

    # Start the process and measure its execution
    $process = Start-Process -FilePath ".\out.exe" -ArgumentList $inputFile, $outputFile -PassThru -NoNewWindow
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $process.WaitForExit()
    $stopwatch.Stop()

    # Obtain peak memory usage data in bytes
    $peakMemoryBytes = $process.PeakWorkingSet64

    # Check if the output matches the expected output
    $result = "Not Matched"
    if (Test-Path $outputFile) {
        $actual = Get-Content $outputFile -Raw
        $expected = Get-Content $expectedOutputFile -Raw
        if ($actual -ceq $expected) {
            $result = "Matched"
        }
    }

    # Output results
    Write-Output "Test Case: marjetice$formattedNumber"
    Write-Output "Duration: $($stopwatch.ElapsedMilliseconds) ms"
    Write-Output "Peak Memory Used: $peakMemoryBytes bytes"
    Write-Output "Output Comparison: $result"
    Write-Output "----------------------------------------"
}
