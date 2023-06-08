#pragma once
#include <vector>
#include <iostream>
#include <string>

class big_integer {
public:
	big_integer(std::string num_) {
		num = num_;
	}
	big_integer(big_integer&& other) {
		num = std::move(other.num);
	}
	big_integer(big_integer& other) = delete;
	big_integer operator+(const big_integer& other);
	big_integer operator*(const big_integer& other);
	big_integer& operator=(big_integer& other) {
		if (&other == this){
			return *this;
		}
		num = other.num;
		return *this;
	}
	big_integer& operator=(big_integer&& other) {
		if (&other == this){
			return *this;
		}
		num = std::move(other.num);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& lhs, big_integer& rhs) {
		lhs << rhs.num;
		return lhs;
	}
private:
	std::string num;
};

big_integer big_integer::operator+(const big_integer& other) {
	int num_len;
	std::string max_num, min_num;
	if (other.num.size() > num.size()) {
		num_len = other.num.size();
		max_num = other.num;
		min_num = num;
	}
	else {
		num_len = num.size();
		max_num = num;
		min_num = other.num;
	}
	std::vector<char> tmp(num_len);
	min_num.insert(min_num.begin(), num_len - min_num.size(), '0');
	std::string num_tmp;
	int num_dec = 0;
	for (int i = num_len - 1; i >= 0; --i) {
		num_tmp = std::to_string(
			static_cast<int>(max_num[i] - '0') +
			static_cast<int>(min_num[i] - '0') +
			num_dec);
		if (num_tmp.size() > 1) {
			tmp.at(i) = num_tmp[1];
			num_dec = static_cast<int>(num_tmp[0] - '0');
		}
		else {
			tmp.at(i) = num_tmp[0];
			num_dec = 0;
		}
	}
	std::string num_new;
	for (const auto& el : tmp) {
		num_new += el;
	}
	big_integer big_integer_tmp(std::move(num_new));
	return big_integer_tmp;
}

big_integer big_integer::operator*(const big_integer& other) {
	int num_len;
	std::string max_num, min_num;
	if (other.num.size() > num.size()) {
		num_len = other.num.size();
		max_num = other.num;
		min_num = num;
	}
	else {
		num_len = num.size();
		max_num = num;
		min_num = other.num;
	}
	std::vector<std::vector<char>> tmp_matrix(num_len);
	std::vector<char> tmp(num_len);
	min_num.insert(min_num.begin(), num_len - min_num.size(), '0');
	std::string num_tmp;
	int num_dec = 0;
	int i = 0;
	for (int i = 0; i < num_len; ++i) {
		for (int j = num_len - 1; j >= 0; --j) {
			num_tmp = std::to_string(
				static_cast<int>(max_num[j] - '0') *
				static_cast<int>(min_num[num_len - i - 1] - '0') +
				num_dec);
			if (num_tmp.size() > 1) {
				tmp.at(j) = num_tmp[1];
				num_dec = static_cast<int>(num_tmp[0] - '0');
			}
			else {
				tmp.at(j) = num_tmp[0];
				num_dec = 0;
			}

		}
		tmp_matrix.at(i) = tmp;
	}
	tmp.clear();
	std::vector<char> num_f;
	std::vector<char> num_s(num_len);

	for (int i = 1; i < num_len; ++i) {
		if (i == 1) {
			num_f = tmp_matrix.at(i - 1);
		}
		num_s = tmp_matrix.at(i);
		num_f.insert(num_f.begin(), 1, '0');
		num_s.insert(num_s.end(), i, '0');
		for (int z = num_f.size() - 1; z >= 0; --z) {
			num_tmp = std::to_string(
				static_cast<int>(num_f[z] - '0') +
				static_cast<int>(num_s[z] - '0') +
				num_dec);
			if (num_tmp.size() > 1) {
				num_f.at(z) = num_tmp[1];
				num_dec = static_cast<int>(num_tmp[0] - '0');
			}
			else {
				num_f.at(z) = num_tmp[0];
				num_dec = 0;
			}
		}
	}


	std::string num_new;
	for (const auto& el : num_f) {
		num_new += el;
	}
	num_new.erase(0, 1);
	big_integer big_integer_tmp(std::move(num_new));
	return big_integer_tmp;
}
