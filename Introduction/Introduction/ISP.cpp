/*
* Interface Seggregation Principle
* 
* The clients should not be forced to implement interfaces they don't use
*/

#include <vector>

struct Document;

/*
=== poor design ===
*/
struct IMachine { // overloaded functionalities
	virtual void print(std::vector<Document*> documents) = 0;
	virtual void scan(std::vector<Document*> documents) = 0;
	virtual void fax(std::vector<Document*> documents) = 0;
};

struct MFH : public IMachine {
	void print(std::vector<Document*> documents) override;
	void scan(std::vector<Document*> documents) override;
	void fax(std::vector<Document*> documents) override;
};

/*
=== better design
*/
struct IPrinter {
	virtual void print(std::vector<Document*> documents) = 0;
};

struct IScanner {
	virtual void scan(std::vector<Document*> documents) = 0;
};

struct Printer : IPrinter {
	void print(std::vector<Document*> documents) override;
};

struct Scanner : IScanner {
	void scan(std::vector<Document*> documents) override;
};

// if wanted something like MFH as above
struct IBMachine : IPrinter, IScanner {};
struct BetterMFH : IBMachine {
	IPrinter& printer;
	IScanner& scanner;

	BetterMFH(IPrinter& printer, IScanner& scanner) : printer { printer }, scanner{ scanner } {}

	void print(std::vector<Document*> documents) {
		printer.print(documents);
	}

	void scan(std::vector<Document*> documents) {
		scanner.scan(documents);
	}
};