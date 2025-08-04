from typing import List, Set
import time

def brute_force_search(main_str: str, substrings: List[str]) -> List[str]:
    """Find substrings using brute force approach"""
    result = [s for s in substrings if s in main_str]
    return result

def create_substring_hashes(main_str: str, max_len: int) -> Set[int]:
    """Create hash set of all possible substrings up to max_len"""
    substring_hashes = set()
    for k in range(1, max_len + 1):
        for i in range(len(main_str) - k + 1):
            substring_hashes.add(hash(main_str[i:i+k]))
    return substring_hashes

def rolling_hash_search(main_str: str, substrings: List[str]) -> List[str]:
    """Find substrings using rolling hash approach"""
    # Get max length to know how many hashes to create
    max_len = max(len(s) for s in substrings) if substrings else 0
    
    # Create hash set of all possible substrings in main_str
    main_str_hashes = create_substring_hashes(main_str, max_len)
    
    # Check which substrings from our list have matching hashes
    result = []
    for substring in substrings:
        substring_hash = hash(substring)
        if substring_hash in main_str_hashes:
            result.append(substring)
    
    return result

def time_function(func, *args, **kwargs):
    """Time a function execution and return result with execution time"""
    start_time = time.perf_counter()
    result = func(*args, **kwargs)
    end_time = time.perf_counter()
    execution_time = (end_time - start_time) * 1000  # Convert to milliseconds
    return result, execution_time

def analyze_time_complexity(main_str: str, substrings: List[str], iterations: int = 10000000):
    """Analyze and compare time complexity of both approaches"""
    print(f"\n=== PERFORMANCE ANALYSIS ===")
    print(f"Main string length: {len(main_str)}")
    print(f"Number of substrings to search: {len(substrings)}")
    print(f"Iterations per test: {iterations}")
    
    # Time brute force approach
    brute_times = []
    for _ in range(iterations):
        _, exec_time = time_function(brute_force_search, main_str, substrings)
        brute_times.append(exec_time)
    
    # Time rolling hash approach  
    rolling_times = []
    for _ in range(iterations):
        _, exec_time = time_function(rolling_hash_search, main_str, substrings)
        rolling_times.append(exec_time)
    
    # Calculate statistics
    brute_avg = sum(brute_times) / len(brute_times)
    rolling_avg = sum(rolling_times) / len(rolling_times)
    brute_min = min(brute_times)
    rolling_min = min(rolling_times)
    brute_max = max(brute_times)
    rolling_max = max(rolling_times)
    
    print(f"\n--- BRUTE FORCE APPROACH ---")
    print(f"Average time: {brute_avg:.4f} ms")
    print(f"Min time: {brute_min:.4f} ms")
    print(f"Max time: {brute_max:.4f} ms")
    print(f"Time Complexity: O(n * m * k) where n=main_str_len, m=num_substrings, k=avg_substring_len")
    
    print(f"\n--- ROLLING HASH APPROACH ---")
    print(f"Average time: {rolling_avg:.4f} ms")
    print(f"Min time: {rolling_min:.4f} ms") 
    print(f"Max time: {rolling_max:.4f} ms")
    print(f"Time Complexity: O(n * max_len + m) where n=main_str_len, max_len=longest_substring, m=num_substrings")
    
    # Performance comparison
    if rolling_avg < brute_avg:
        speedup = brute_avg / rolling_avg
        print(f"\n🚀 Rolling hash is {speedup:.2f}x FASTER than brute force!")
    elif brute_avg < rolling_avg:
        slowdown = rolling_avg / brute_avg
        print(f"\n⚠️ Rolling hash is {slowdown:.2f}x SLOWER than brute force!")
    else:
        print(f"\n🤝 Both approaches have similar performance!")
    
    # Analysis of why rolling hash might be slower for small inputs
    print(f"\n--- ANALYSIS ---")
    total_substrings_generated = sum(len(main_str) - k + 1 for k in range(1, max(len(s) for s in substrings) + 1))
    print(f"Rolling hash generates {total_substrings_generated} substrings and hashes")
    print(f"Brute force only checks {len(substrings)} substrings")
    print(f"For small inputs, brute force wins due to:")
    print(f"  • Python's optimized string operations")
    print(f"  • Lower overhead for small datasets") 
    print(f"  • Rolling hash preprocessing cost")
    print(f"\nRolling hash benefits become apparent with:")
    print(f"  • Very long main strings")
    print(f"  • Many substrings to search")
    print(f"  • Repeated searches on same text")
    
    return brute_avg, rolling_avg

def main() -> None:
    """Main function - entry point of the program"""
    main_str = "hellotherehowareyou"
    substrings = ["hello", "there", "how", "are", "you", "test", "youare", "hellothere"]
    max_len = max(len(s) for s in substrings)
    
    print("=== FUNCTIONALITY TEST ===")
    
    # Brute force approach with timing
    brute_result, brute_time = time_function(brute_force_search, main_str, substrings)
    print(f"Brute force result: {brute_result}")
    print(f"Brute force time: {brute_time:.4f} ms")
    
    # Rolling hash approach with timing
    rolling_result, rolling_time = time_function(rolling_hash_search, main_str, substrings)
    print(f"Rolling hash result: {rolling_result}")
    print(f"Rolling hash time: {rolling_time:.4f} ms")
    
    # Create substring hashes for analysis
    substring_hashes = create_substring_hashes(main_str, max_len)
    print(f"Created {len(substring_hashes)} unique substring hashes")
    
    # Verify both methods give same result
    print(f"Both methods match: {brute_result == rolling_result}")
    
    # Show why rolling hash is slower for small inputs
    print(f"\n=== WHY ROLLING HASH IS SLOWER ===")
    print(f"Brute force operations:")
    print(f"  • Only checks {len(substrings)} substrings")
    print(f"  • Uses Python's optimized 'in' operator (written in C)")
    print(f"  • No preprocessing needed")
    
    total_operations = sum(len(main_str) - k + 1 for k in range(1, max_len + 1))
    print(f"\nRolling hash operations:")
    print(f"  • Generates {total_operations} substrings")
    print(f"  • Computes {total_operations} hash values (slow in Python)")
    print(f"  • Creates and manages hash set")
    print(f"  • Then checks {len(substrings)} hash lookups")
    
    print(f"\nRatio: Rolling hash does {total_operations}/{len(substrings)} = {total_operations/len(substrings):.1f}x more work!")
    
    # Performance analysis
    analyze_time_complexity(main_str, substrings, iterations=1000)

# This is the Python idiom for "run main() only if this file is executed directly"
if __name__ == "__main__":
    main()  