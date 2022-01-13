# emojilang
Programming language where you can code using emojis 😌

### To execute
First make sure you have python(version 3.x) and pip installed
#### First clone it
````bash
    #First Clone It
    git clone https://github.com/grininja/emojilang.git emojilang
    #Navigate into the directory
    cd emojilang
    #Install the requirements
    pip install -r requirements.txt
````

#### Then execute your source file
````bash
    python main.py <Your File Path>
    # for example
    python main.py /tests/firstPrimes.emo
````
Or 
````bash
    python3 main.py /tests/firstPrimes.emo
````

### Syntax

| emoji | Semantic|
|-------|--------|
|✖,➕, ➖, ➗, 📎 | *, +, -, / ,% |
|💿,📀 |while, for |
| 🚩, 🏁, 🏳 | if ,else, elif |
| ⏸,⏩| break, continue  |
|😌,😌😌,😁,😭,😁😌,😭😌,❗😌|=, == ,>, <,>=,<=,!=|
|⚛ , ☯, ⚓, 〰|(bitwise) &, \|, ^, ~|
| 😠, 😇, ❗|(logical) and, or, not|
|💩 comments starts with '💩'|comments|
|📢|used to declare variable|
|🖨|print on console|
|👉, 👈 |(, )|
|🍽,🥂| {, }|
|🗿|, (comma)|
|👄|; (semicolon)|
|✔, ❌|true, false|
<!-- #### Operators
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
|logical xor | xor <br> ^| -->

<!-- #### Operators Precedence
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
|logical or|or, \|\|| -->

### Sample Codes
#### Variable Declaration

````
    📢 a 💩 declares the valriable a
    📢 b 😌 5🗿 c🗿 d 😌 6 💩 declares a, c, d and assigns them 5, None, 6 respectively 
    📢 e 😌 5➕c✖4 💩 equivalent to decl e = 5+c*4
    📢 t 😌 ✔🗿 f 💩 decl t = true, f
````
👉, 👈
#### Assignments
````
    a 😌 3
    b 😌 👉c✖4👈➕5 ➗ d
    f 😌 ❌
    💩 Equivalent to
    💩 a = 3
    💩 b = (c*4) + 5 / d
    💩 f = false

````
<!-- #### Flow Control
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
```` -->
<!-- #### Branching
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
    } -->
<!-- ```` -->

<!-- ### Invalid Syntaxes
````
    #INVALID
    if(a==5)
        print(a)
    
    #VALID
    if(a==5){
        print(a)
    }
    

    #similarly for other blocks like for and while
```` -->
### Fibonacci Series
````
    📢 f0 😌 0 🗿 f1 😌 1
    📢 i 😌 0
    💿👉i 😭 10👈🍽
        🖨👉f0👈
        📢 tmp 😌 f0
        f0 😌 f1
        f1 😌 f1 ➕ tmp
        i 😌 i ➕ 1
    🥂

💩 Equivalent to
💩 decl f0 = 0, f1 = 1
💩 i = 0
💩 while(i < 10){
💩    print(f0)
💩    decl tmp = f0
💩    f0 = f1
💩    f1 = f1 + tmp
💩    i = i + 1
💩 }

````
### Prime Numbers
````
    📢 start 😌 2 🗿 end 😌 100
    📀👉📢 n😌start👄n😭😌end👄 n 😌 n➕1👈🍽
        📢 flag 😌 ✔
        📀👉📢 i😌n➖1👄 i 😁 1👄 i 😌 i ➖ 1👈🍽
            🚩👉n 📎 i 😌😌 0👈🍽
                flag 😌 ❌
                ⏸
            🥂
        🥂
        🚩👉flag👈🍽
            🖨👉n👈
        🥂
    🥂

💩Equivalent to
💩decl start = 2, end = 100
💩for(decl n = start; n <= end; n = n+1){
💩  flag = true 
💩  for(decl i = n-1; i > 1; i = i - 1){
💩      if(n%i == 0){
💩           flag = false
💩      }
💩  }   
💩  if(flag){
💩      print(n)
💩  }
💩}

````

