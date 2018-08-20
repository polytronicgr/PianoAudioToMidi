#pragma once

class KerasError : public std::exception
{
public:
#pragma warning(suppress:4514)	// Unreferenced inline function has been removed
	explicit KerasError(const char* msg = "Unknown exception") noexcept : errMsg_(msg) {}
	virtual ~KerasError() override final = default;
	virtual const char* what() const override final { return errMsg_.c_str(); }
private:
	std::string errMsg_;
};