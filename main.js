class RollingHashSet {
    constructor() {
        this.substringHashes = new Set();
    }

    // Brute force search function
    bruteForceSearch(mainStr, substrings) {
        return substrings.filter(substr => mainStr.includes(substr));
    }

    // Create substring hashes
    createSubstringHashes(mainStr, maxLen) {
        const hashes = new Set();
        
        for (let k = 1; k <= maxLen; k++) {
            for (let i = 0; i <= mainStr.length - k; i++) {
                const substring = mainStr.substring(i, i + k);
                // Simple hash function (not cryptographically secure)
                hashes.add(this.simpleHash(substring));
            }
        }
        
        return hashes;
    }

    // Simple hash function for strings
    simpleHash(str) {
        let hash = 0;
        for (let i = 0; i < str.length; i++) {
            const char = str.charCodeAt(i);
            hash = ((hash << 5) - hash) + char;
            hash = hash & hash; // Convert to 32-bit integer
        }
        return hash;
    }

    // Find max length in array of strings
    findMaxLength(strings) {
        return Math.max(...strings.map(str => str.length));
    }
}

// Main function
function main() {
    const rhs = new RollingHashSet();
    
    const mainStr = "hellotherehowareyou";
    const substrings = ["hello", "there", "how", "are", "you", "test", "youare", "hellothere"];
    
    // Brute force approach
    const result = rhs.bruteForceSearch(mainStr, substrings);
    console.log(`Brute force result: [${result.map(s => `"${s}"`).join(", ")}]`);
    
    // Create substring hashes
    const maxLen = rhs.findMaxLength(substrings);
    const substringHashes = rhs.createSubstringHashes(mainStr, maxLen);
    console.log(`Created ${substringHashes.size} unique substring hashes`);
    
    // Optional: Show some example hashes
    console.log(`\nExample hashes:`);
    const hashArray = Array.from(substringHashes).slice(0, 5);
    hashArray.forEach((hash, index) => {
        console.log(`Hash ${index + 1}: ${hash}`);
    });
}

// Run the main function
main();

// Export for use as module (optional)
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { RollingHashSet };
}
