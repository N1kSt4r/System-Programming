Creator.exe
	Create binary file, which name and number of records gets from command line

Reporter.exe
	Create text file, which contains sorted list of companies, which tax more or less,
then given value
	Reporter gets:
		o Name of binary file
		o Name of report file
		o Tax value
		o Symbol '<' or '>' (means less or more)
	Report contains:
		o Title
		o List of companies. Every line contains information from binary file

Main
	Gets from console name of binary file and number of records. Run and wait Creator.
Run and wair Reporter. Show report on console
