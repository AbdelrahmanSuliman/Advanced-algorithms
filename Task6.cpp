#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <algorithm>

std::vector<std::string> wrap_text(const std::vector<std::string>& word_list, int max_line_width) {
    int word_count = word_list.size();

    std::vector<int> dp_table(word_count + 1, INT_MAX);
    std::vector<int> break_points(word_count + 1, -1);  
    dp_table[0] = 0;   

    for (int i = 1; i <= word_count; i++) {
        int current_length = -1;  
        for (int j = i; j >= 1; j--) {
            current_length += word_list[j - 1].size() + 1;
            if (current_length > max_line_width) break;

            int line_cost = (current_length == max_line_width) ? 0 : (max_line_width - current_length) * (max_line_width - current_length);

            if (dp_table[j - 1] != INT_MAX && dp_table[j - 1] + line_cost < dp_table[i]) {
                dp_table[i] = dp_table[j - 1] + line_cost;
                break_points[i] = j - 1; 
            }
        }
    }


    std::vector<std::string> wrapped_lines;
    int current_index = word_count;
    while (current_index > 0) {
        int start_index = break_points[current_index];
        std::string line = "";
        for (int i = start_index; i < current_index; i++) {
            if (i != start_index) line += " ";
            line += word_list[i];
        }
        wrapped_lines.push_back(line);
        current_index = start_index;  
    }

    std::reverse(wrapped_lines.begin(), wrapped_lines.end());  
    return wrapped_lines;
}

int main() {
    
    std::string sentence = "This is an example sentence that will be wrapped according to the specified line width.";
    int line_width = 20;

    
    std::vector<std::string> words;
    std::istringstream iss(sentence);
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

    
    for (const auto& word : words) {
        if (word.length() > line_width) {
            std::cerr << "Word '" << word << "' is longer than the line width.\n";
            return 1;
        }
    }

    
    std::vector<std::string> wrapped_text = wrap_text(words, line_width);

    
    for (size_t i = 0; i < wrapped_text.size(); ++i) {
        std::cout << "line " << i + 1 << ": " << wrapped_text[i] << std::endl;
    }

    return 0;
}
