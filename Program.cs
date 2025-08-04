using System;
using System.Collections.Generic;
using System.Linq;

namespace RollingHashSet
{
    class Program
    {
        static void Main(string[] args)
        {
            string mainStr = "hellotherehowareyou";
            string[] substrings = {"hello", "there", "how", "are", "you", "test", "youare", "hellothere"};
            
            // Brute force approach
            var result = BruteForceSearch(mainStr, substrings);
            Console.WriteLine($"Brute force result: [{string.Join(", ", result)}]");
            
            // Create substring hashes
            var substringHashes = CreateSubstringHashes(mainStr, substrings.Max(s => s.Length));
            Console.WriteLine($"Created {substringHashes.Count} unique substring hashes");
        }
        
        static List<string> BruteForceSearch(string mainStr, string[] substrings)
        {
            return substrings.Where(s => mainStr.Contains(s)).ToList();
        }
        
        static HashSet<int> CreateSubstringHashes(string mainStr, int maxLen)
        {
            var substringHashes = new HashSet<int>();
            
            for (int k = 1; k <= maxLen; k++)
            {
                for (int i = 0; i <= mainStr.Length - k; i++)
                {
                    substringHashes.Add(mainStr.Substring(i, k).GetHashCode());
                }
            }
            
            return substringHashes;
        }
    }
}
