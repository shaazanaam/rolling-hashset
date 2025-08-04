#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <numeric>

class RollingHashSet {
private:
    std::unordered_set<size_t> substring_hashes;

public:
    // Brute force search function
    std::vector<std::string> bruteForceSearch(const std::string& main_str, 
                                              const std::vector<std::string>& substrings) {
        std::vector<std::string> result;
        
        for (const auto& substr : substrings) {
            if (main_str.find(substr) != std::string::npos) {
                result.push_back(substr);
            }
        }
        
        return result;
    }
    
    // Create substring hashes
    std::unordered_set<size_t> createSubstringHashes(const std::string& main_str, int max_len) {
        std::unordered_set<size_t> hashes;
        
        for (int k = 1; k <= max_len; k++) {
            for (int i = 0; i <= static_cast<int>(main_str.length()) - k; i++) {
                std::string substring = main_str.substr(i, k);
                hashes.insert(std::hash<std::string>{}(substring));
            }
        }
        
        return hashes;
    }
    
    // Rolling hash search function
    std::vector<std::string> rollingHashSearch(const std::string& main_str, 
                                              const std::vector<std::string>& substrings) {
        if (substrings.empty()) return {};
        
        int max_len = findMaxLength(substrings);
        auto main_str_hashes = createSubstringHashes(main_str, max_len);
        
        std::vector<std::string> result;
        for (const auto& substring : substrings) {
            size_t substring_hash = std::hash<std::string>{}(substring);
            if (main_str_hashes.find(substring_hash) != main_str_hashes.end()) {
                result.push_back(substring);
            }
        }
        
        return result;
    }
    
    // Timing function
    template<typename Func, typename... Args>
    std::pair<std::vector<std::string>, double> timeFunction(Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        double milliseconds = duration.count() / 1000000.0;
        
        return std::make_pair(result, milliseconds);
    }
    
    // Performance analysis
    void analyzePerformance(const std::string& main_str, 
                           const std::vector<std::string>& substrings, 
                           int iterations = 1000) {
        std::cout << "\n=== PERFORMANCE ANALYSIS ===" << std::endl;
        std::cout << "Main string length: " << main_str.length() << std::endl;
        std::cout << "Number of substrings to search: " << substrings.size() << std::endl;
        std::cout << "Iterations per test: " << iterations << std::endl;
        
        // Time brute force approach
        std::vector<double> brute_times;
        for (int i = 0; i < iterations; i++) {
            auto [result, exec_time] = timeFunction([this](const std::string& str, const std::vector<std::string>& subs) {
                return this->bruteForceSearch(str, subs);
            }, main_str, substrings);
            brute_times.push_back(exec_time);
        }
        
        // Time rolling hash approach
        std::vector<double> rolling_times;
        for (int i = 0; i < iterations; i++) {
            auto [result, exec_time] = timeFunction([this](const std::string& str, const std::vector<std::string>& subs) {
                return this->rollingHashSearch(str, subs);
            }, main_str, substrings);
            rolling_times.push_back(exec_time);
        }
        
        // Calculate statistics
        double brute_avg = std::accumulate(brute_times.begin(), brute_times.end(), 0.0) / brute_times.size();
        double rolling_avg = std::accumulate(rolling_times.begin(), rolling_times.end(), 0.0) / rolling_times.size();
        double brute_min = *std::min_element(brute_times.begin(), brute_times.end());
        double rolling_min = *std::min_element(rolling_times.begin(), rolling_times.end());
        double brute_max = *std::max_element(brute_times.begin(), brute_times.end());
        double rolling_max = *std::max_element(rolling_times.begin(), rolling_times.end());
        
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "\n--- BRUTE FORCE APPROACH ---" << std::endl;
        std::cout << "Average time: " << brute_avg << " ms" << std::endl;
        std::cout << "Min time: " << brute_min << " ms" << std::endl;
        std::cout << "Max time: " << brute_max << " ms" << std::endl;
        
        std::cout << "\n--- ROLLING HASH APPROACH ---" << std::endl;
        std::cout << "Average time: " << rolling_avg << " ms" << std::endl;
        std::cout << "Min time: " << rolling_min << " ms" << std::endl;
        std::cout << "Max time: " << rolling_max << " ms" << std::endl;
        
        // Performance comparison
        if (rolling_avg < brute_avg) {
            double speedup = brute_avg / rolling_avg;
            std::cout << "\n🚀 Rolling hash is " << speedup << "x FASTER than brute force!" << std::endl;
        } else {
            double slowdown = rolling_avg / brute_avg;
            std::cout << "\n⚠️ Rolling hash is " << slowdown << "x SLOWER than brute force!" << std::endl;
        }
        
        // Analysis
        std::cout << "\n--- ANALYSIS ---" << std::endl;
        int max_len = findMaxLength(substrings);
        int total_operations = 0;
        for (int k = 1; k <= max_len; k++) {
            total_operations += static_cast<int>(main_str.length()) - k + 1;
        }
        
        std::cout << "Rolling hash generates " << total_operations << " substrings and hashes" << std::endl;
        std::cout << "Brute force only checks " << substrings.size() << " substrings" << std::endl;
        std::cout << "Ratio: Rolling hash does " << total_operations << "/" << substrings.size() 
                  << " = " << (double)total_operations/substrings.size() << "x more work!" << std::endl;
    }
    
    // Find max length in vector of strings
    int findMaxLength(const std::vector<std::string>& strings) {
        int max_len = 0;
        for (const auto& str : strings) {
            max_len = std::max(max_len, static_cast<int>(str.length()));
        }
        return max_len;
    }
};

int main() {
    RollingHashSet rhs;
    
    std::string main_str = "hellotherehowareyou";
    std::vector<std::string> substrings = {
        "hello", "there", "how", "are", "you", "test", "youare", "hellothere"
    };
    
    std::cout << "=== FUNCTIONALITY TEST ===" << std::endl;
    
    // Brute force approach with timing
    auto [brute_result, brute_time] = rhs.timeFunction([&rhs](const std::string& str, const std::vector<std::string>& subs) {
        return rhs.bruteForceSearch(str, subs);
    }, main_str, substrings);
    
    std::cout << "Brute force result: [";
    for (size_t i = 0; i < brute_result.size(); i++) {
        std::cout << "\"" << brute_result[i] << "\"";
        if (i < brute_result.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Brute force time: " << brute_time << " ms" << std::endl;
    
    // Rolling hash approach with timing
    auto [rolling_result, rolling_time] = rhs.timeFunction([&rhs](const std::string& str, const std::vector<std::string>& subs) {
        return rhs.rollingHashSearch(str, subs);
    }, main_str, substrings);
    
    std::cout << "Rolling hash result: [";
    for (size_t i = 0; i < rolling_result.size(); i++) {
        std::cout << "\"" << rolling_result[i] << "\"";
        if (i < rolling_result.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "Rolling hash time: " << rolling_time << " ms" << std::endl;
    
    // Create substring hashes for analysis
    int max_len = rhs.findMaxLength(substrings);
    auto substring_hashes = rhs.createSubstringHashes(main_str, max_len);
    std::cout << "Created " << substring_hashes.size() << " unique substring hashes" << std::endl;
    
    // Verify both methods give same result
    std::cout << "Both methods match: " << (brute_result == rolling_result ? "true" : "false") << std::endl;
    
    // Performance analysis
    rhs.analyzePerformance(main_str, substrings, 1000);
    
    return 0;
}
