#pragma once
#include <vector>


template<typename T>
class Distributor
{
private:
	size_t vector_count;
	std::vector<std::vector<T>> input;
	std::vector<std::vector<T>> output;
	std::vector<T> current_construct;

public:
	
	Distributor(std::vector<std::vector<T>> input_)
	{
		for (auto& v : input_)
		{
			if (v.size() > 0)
			{
				input.push_back(v);
			}
		}

		vector_count = input_.size();
		
		if (vector_count > 0)
		{
			backtrack(0);
		}
	};

	std::vector<std::vector<T>> get_result()
	{
		return output;
	}

private:
	void backtrack(size_t arr_num)
	{
		if (arr_num >= vector_count)
		{
			output.push_back(current_construct);
		}

		else
		{
			for (size_t i = 0; i < input[arr_num].size(); i++)
			{
				current_construct.push_back(input[arr_num][i]);
				backtrack(arr_num + 1);
				current_construct.pop_back();
			}
		}
	};
};

