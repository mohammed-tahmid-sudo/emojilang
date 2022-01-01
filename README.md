# emojilang
Programming language where you can code using emojis 😌

#### To install dependencies
```bash
pip install -r requirements.txt
```

### Current Syntax

#### Operators
|Operation | Symbol|
|---------|-----|
|unary not|not<br>!|
|unary complement|~|
|bitwise and|        &|
|bitwise or|  \| |
|bitwise xor| ^<br> xor
|bitwise complement | ~
|logical and | and <br> &&
|logical or  | or <br> \|\| |
|logical not | not <br> !
|logical xor | xor <br> ^|

#### Operators Precedence
<mark>Operators With Highest Priority On Top</mark><br>
|Description|Operators|
|----|-----|
|unary oprators|not, !, ~ |
|arithmatic|*, /, %|
|arithmatic|+, -|
|comparison|==, !=, <=, <, >, => <br><mark>*Python's Precedence</mark>|
|bitwise and|&|
|bitwise xor|^, xor|
|bitwise or|\||
|logical and|and, &&|
|logical or|or, \|\||


#### Variable Declaration

````
    decl a
    decl b=5, c, d=6
    decl e=5+c*4
    decl t = true, f
````
#### Assignments
````
    a = 3
    b = (c*4)+5 / d
    f = false
````
#### Flow Control
````
    while(a <= 5*b){
        #this is how you use comments
        #statements
    }
    while(){
        #infinite looop
    }
    for(decl i=0, j=7, k; i < a*5; i = i+1, b=b*(28 +)){
        #declared i, j, k and assigned values to i and j
        #statements
    }
    for( ; ; ){
        #all three statements can be skipped
    }
````
#### Branching
````
    if(a == 5){
        #statements
    }
    elif(a<5){
        #statements
    }
    elif(a>5 || a&b|c){
        #statements
    }
    else{
        #statements
    }
````

### Invalid Syntaxes
````
    #INVALID
    if(a==5)
        print(a)
    
    #VALID
    if(a==5){
        print(a)
    }
    

    #similarly for other blocks like for and while
````

### emoji and keywords
| EMOJI | UNICODE | KEYWORDS|
|-------|---------|--------|
|0️⃣,1️⃣,2️⃣,3️⃣,4️⃣|U+30, U+31, U+32, U+33, U+34| 0,1,2,3,4|
|5️⃣,6️⃣,7️⃣,8️⃣,9️⃣ | U+35, U+36 U+37,U+38,U+39|5,6,7,8,9 | 
| ✖️,➕, ➖, ➗,󠀥 󠀥﹪ |  U+2716, U+2795, U+2796,  U+2797 , U+E0025, U+FE6A  | *, +, -, / ,% |
|🌀,❤️ |U+1F300, U+2764 |while, for |
| 🔥, 🌊,✨  | U+1F525, U+1F30A, U+2728 | if ,else, elif |
| 💔, ⚙️ | U+1F494, U+2699  | break, continue  |
|😐, 😏,😫, 😁,😬, 😶|  U+1F610, U+1F60F, U+1F62B, U+1F601,U+1F62C, U+1F636|= ,>, <,>=,<=,!=|





