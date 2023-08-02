#pragma once


class Exception :public exception
{
	str _text;
	int _line;
	str _source;
	str _time;
	str _date;
public:
	Exception(str text = "exception", int line = 0, str source = "", str time = "", str date = "") :exception(text.c_str())
	{
		this->_line = line;
		this->_source = source;
		this->_time = time;
		this->_date = date;
		this->_text = "Message: " + str(exception::what())
			+ " | Source: " + this->_source
			+ " | Time: " + this->_time
			+ " | Date: " + this->_date
			+ " | Line: " + to_string(this->_line);
	}

	char const* what()const override { return this->_text.c_str(); }

};

class DatabaseException :public Exception
{
public:
	DatabaseException() :Exception() {}
	DatabaseException(str text = "Database exception", int line = 0, str source = "", str time = "", str date = "") :Exception(text, line, source, time, date) {}
};

class InvalidArgument :public Exception
{
public:
	InvalidArgument() :Exception() {}
	InvalidArgument(str text = "InvalidArgument exception", int line = 0, str source = "", str time = "", str date = "") :Exception(text, line, source, time, date) {}
};