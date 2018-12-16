# The Ziv-Lempel Algorithm 
* Lempel–Ziv–Welch. Lempel–Ziv–Welch (LZW) is a universal lossless data compression algorithm created by **Abraham Lempel, Jacob Ziv, and Terry Welch.**  
* Is the basis for most popular compression programs
such as **winzip, zip or gzip.** 

## How It Works

#### Compression:
- The Ziv-Lempel compression method maps strings of input characters into numeric codes. All characters (the alphabet) are assigned a `code`. 
  
* The dictionary hols the mapping between character strings and their codes. Each
dictionary entry has two fields: `key` and `code`. The character string represented by
code is stored in the field key. 

* The Ziv-Lempel compressor
repeatedly finds the longest prefix, `p`, of the unencoded part of the input file that is
in the dictionary and outputs its code. If there is a next character `c` in the input file,
then `pc` (`pc` is the prefix string `p` followed by the character `c`) is assigned the next code
and inserted into the dictionary. This strategy is called the **Ziv-Lempel rule**. 

#### Decompression
* Input the
codes one at a time and replace them by the texts they denote. The **_code-to-text_**
mapping can be reconstructed in the following way. 

* The codes assigned for single
character texts are entered into the dictionary at the initialization (just as we did for
compression). As before, the dictionary entries are code-text pairs. This time,
however, the dictionary is searched for an entry with a given code (rather than with a
given string). 
* The first code in the compressed file must correspond to a single 
3 character and so may be replaced by the corresponding character (which is
already in the dictionary!) 

    **For all other codes x in the compressed file, we have two
cases to consider:**  
1. The code `x` is already in the dictionary: When x is in the dictionary, the
corresponding text, `text(x)`, to which it corresponds, is extracted from the
dictionary and output. Also, from the working of the compressor, we know
that if the code that precedes `x` in the compressed file is `q` and `text (q)` is
the corresponding text, then the compressor would have created a new
code for the text `text(q)` followed by the first character (that we will denote
by `fc(x`)), of `text(x)` So, we enter the
pair (next code, `text(q)fc(p)`) into the dictionary.

2. The code `x` is NOT in the dictionary: This case arises only when the
current text segment has the form `text(q)text(q)fc(q)` and `text(x)` =
`text(q)fc(q)` The corresponding
compressed file segment is `qx`. During compression, `text(q)fc(q)` is
assigned the code `x`, and the code `x` is output for the text `text(q)fc(q)`.
During decompression, after `q` is replaced by `text(q)`, we encounter the
code `x`. However, there is no code-to-text mapping for `x` in our table. We
are able to decode `x` using the fact that this situation arises only when the
decompressed text segment is `text(q)text(q)fc(q)`. When we encounter a
code `x` for which the code-to-text mapping is undefined, the code-to-text
mapping for `x` is `text(q)fc(q)`, where q is the code that precedes `x` in the
file.
##Program Flow
#### Compression:
The string is read from `"compin.txt"` and compressed into output in `"compout.txt"`
#### Decompression:
The compressed data is read from `"compout.txt"` and decompressed into `"decompout.txt"`

## The Folders and Files

`compress-program:` Folder contains compression program as `main.ccp` and a hashTable implementation inside `HashTable.cpp`  

`decompress-program:` Folder contains decompression program as `main.ccp`


## Example

* For the sake of demonstration with a short string Dictionary is only initialized with   
`0 -> a`  
`1 -> b`  
in both cases!  

#### Compression
* For two character input string for compression
`aaabbbbbbaabaaba` is put into dictionary as:   
* The string `'aa' (p =
“a” and c = ‘a’)` is assigned the code `2` and entered into the dictionary. `“aa”` is the
longest prefix of the remaining string that is in the dictionary.  
* Its code, `2`, is output;
* The string `“aab” (p = “aa”, c =’b’)` is assigned the code `3` and entered into the
dictionary. Notice that even though `'aab'` has the code `3` assigned to it, only the code `2`
for `'aa'` is output. The suffix `'b'` will be part of the next code output. 
* The reason for not
outputting `3` is that the code table is not part of the compressed file. Instead, the code
table has to be reconstructed during decompression using the compressed file. This
reconstruction is possible only if we adhere strictly to the Lempel-Ziv rule.
* Following the output of the code `2`, the code for `'b'` is output; `“bb”` is assigned the code
`4` and entered into the code dictionary. Then, the code for `“bb”` is output, and `“bbb”` is
entered into the table with code `5`. 
* Next, the code `5` is output, and `“bbba”` is entered
with code `6`. Then, the code `3` is output for `“aab”`, and `“aaba”` is entered into the
dictionary with code `7`. 
* The code `7` is output for the remaining string `'aaba'`.
`0 -> a`  
`1 -> b`  
`2 -> aa`  
`3 -> aab`  
`4 -> bb`  
`5 -> bbb`  
`6 -> bbba`  
`7 -> aaba`  
        
        Hence, Output is: `0 2 1 4 5 3 7`

#### Decompression
* Input: `0 2 1 4 5 3 7` 
- The first code in the compressed file is `0` which is replaced by `'a'`.
- The next code, `2`, is undefined. Since `text (0) = 'a'`,
`fc(0)='a'` then `text(2) = text(0)fc(0) = 'aa'`. Therefore given code 2 is output `'aa' `, and `(2,
'aa')` is entered into the dictionary.
* The next code, `1`, is replaced by `text(1) = ‘b’` and `(3, text(2)fc(l) ) = (3, 'aab')` is
entered into the dictionary.
* The next code, `4`, is not in the dictionary. The code preceding it is `1` and so
`text(4)= text(l)fc(l)= 'bb'`. The pair `(4, 'bb')` is entered into the dictionary, and
`'bb'` is output to the decompressed file.
* When the next code, `5`, is encountered,`(5, 'bbb')` is entered into the dictionary
and `'bbb'` is output to the decompressed file. 
* The next code is `3` which is already in the dictionary so `text(3) = 'aab'` is
output to the decompressed file, and the pair `(6, text (5)fc(3)) = (6, 'bbba')` is
entered into the dictionary.
* The next code `7` is encountered, `(7, text(3)fc(3)) = (7, 'aaba')` is
entered into the dictionary and `'aaba'` output.   
    
        Therefore the Output: `aaabbbbbbaabaaba`
