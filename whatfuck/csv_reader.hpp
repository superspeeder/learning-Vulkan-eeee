#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

class CSVReader {
private:
	std::ifstream infile;
	size_t linesRead = 0;
public:

	CSVReader(const char* path) : infile(path) {

	}

	bool isAtEnd() {
		return infile.peek() == EOF;
	}

	std::string readLineRaw() {
		std::string line;
		std::getline(infile, line);
		linesRead++;
		return line;
	}

	std::vector<std::string> readNextLine() {
		std::vector<std::string> line;
		
		std::string line_raw = readLineRaw();

		std::string cur_element;

		for (size_t i = 0; i < line_raw.size(); i++) {
			char c = line_raw[i];
			if (c == ',') {
				line.push_back(cur_element);
				cur_element = "";
			}
			else {
				cur_element.push_back(c);
			}
		}
		if (cur_element.size() > 0) {
			line.push_back(cur_element);
		}

		return line;
	}

	template <size_t N>
	std::array<std::vector<std::string>, N> readLines() {
		std::array<std::vector<std::string>, N> lines;
		for (size_t i = 0; i < N; i++) {
			lines[i] = readNextLine();
		}
	}
};