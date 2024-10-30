const THREE_HOURS_IN_SECONDS: u16 = 60 * 60 * 3;

fn a_in_hiragana() -> char {
    'あ' // no semicolon -> expression
}

fn fibonacci(values: &mut [u128]) {
    match values.len() {
        0 => {},
        1 => values[0] = 1,
        2 => {
            values[0] = 1;
            values[1] = 1;
        },
        _ => {
            values[0] = 1;
            values[1] = 1;

            for i in 2..values.len() {
                values[i] = values[i - 1] + values[i - 2];
            }
        }
    }
}

fn poisson(lambda: f64, k: u32) -> f64 {
    let k_factorial = (1..=k).fold(1, |acc, x| acc * x);
    let e_to_the_minus_lambda = (-lambda).exp();

    (lambda.powi(k as i32) * e_to_the_minus_lambda) / k_factorial as f64
}

fn is_odd(n: usize) -> bool {
    n % 2 == 1
}

fn is_even(n: usize) -> bool {
    !is_odd(n)
}

fn main() {
    // Variables and Mutability
    println!("\nVariables and Mutability\n");
    let immutable = 1;
    let mut mutable = 1;

    println!("The value of constant is: {}", THREE_HOURS_IN_SECONDS);
    println!("The value of immutable is: {}", immutable);
    println!("The value of mutable is: {}", mutable);

    // immutable = 2; error[E0384]: cannot assign twice to immutable variable `immutable`

    mutable = 2;
    println!("The value of mutable is: {}", mutable);

    // Shadowing
    println!("\nShadowing\n");

    let shadow = 1;

    let shadow = shadow + 1;

    {
        let shadow = shadow * 2;
        println!("The value of shadow in the inner scope is: {}", shadow);
    }

    println!("The value of shadow is: {}", shadow);

    // Data Types
    println!("\nData Types\n");

    let guess: u32 = "42".parse().expect("Not a number!");
    // let guess: u32 = "42.0".parse().expect("Not a number!"); thread 'main' panicked at 'Not a number!: ParseIntError { kind: InvalidDigit }'
    // let guess = "42".parse().expect("Not a number!"); error[E0282]: type annotations needed

    let float: f32 = "42.1".parse().expect("Not a number!");
    let int: f32 = float;
    let int: i32 = int.trunc() as i32;

    println!("The value of guess is: {}", guess);
    println!("The value of float is: {}", float);
    println!("The value of int is: {}", int);

    /*
        Scalar Types
        ------------

        A scalar type represents a single value. Rust has four primary scalar types:
        integers, floating-point numbers, Booleans, and characters.
    */
    println!("\nScalar Types\n");

    /*
        Integer Types
        -------------

        Signed integers: i8, i16, i32, i64, i128 and isize (pointer size)
        Unsigned integers: u8, u16, u32, u64, u128 and usize (pointer size)
        
        The isize and usize types depend on the architecture of the computer your
        program is running: 64 bits if you’re on a 64-bit architecture and 32 bits
        with a 32-bit architecture.
    */

    let eightbit: u8 = b'A';
    let binary: u8 = 0b1111_0000;
    let sixteenbit: u16 = 0xFf;

    // let unsigned: u8 = -1; error[E0600]: cannot apply unary operator `-` to type `u8`
    let signed: i8 = -1;

    let unsigned_128: u128 = std::u128::MAX;
    let another_unsigned_128: u128 = 2_u128.pow(127) + (2_u128.pow(127) - 1);

    println!("The value of eightbit is: {}", eightbit);
    println!("The value of binary is: {}", binary);
    println!("The value of sixteenbit is: {}", sixteenbit);
    println!("The value of signed is: {}", signed);
    println!("The value of unsigned_128 is: {}", unsigned_128);
    println!("The value of another_unsigned_128 is: {}", another_unsigned_128);

    /*
        Floating-Point Types
        --------------------

        f32, f64

        The default type is f64 because on modern CPUs, it's roughly the same
        speed as f32 but is capable of more precision.
    */
    println!("\nFloating-Point Types\n");

    let floating64 = 3.14; // f64
    let floating32: f32 = 3.14; // f32

    println!("The value of floating64 is: {}", floating64);
    println!("The value of floating32 is: {}", floating32);

    /*
        Numeric Operations
        ------------------

        +, -, *, /, %
    */
    println!("\nNumeric Operations\n");

    let sum = 5 + 10;
    let difference = 95.5 - 4.3;
    let product = 4 * 30;
    let quotient = 56.7 / 32.2;
    let truncated = 43 / 5;
    let remainder = 43 % 5;

    println!("The value of sum is: {}", sum);
    println!("The value of difference is: {}", difference);
    println!("The value of product is: {}", product);
    println!("The value of quotient is: {}", quotient);
    println!("The value of truncated is: {}", truncated);
    println!("The value of remainder is: {}", remainder);

    // Boolean Type
    println!("\nBoolean Type\n");

    let t = true;
    let f: bool = false;

    println!("The value of t is: {}", t);
    println!("The value of f is: {}", f);
    println!("The value of t && !f is: {}", t && !f);
    println!("Morgan's Law: !(t && f) == !t || !f is {}", !(t && f) == !t || !f);

    /*
        Char Type
        ---------

        Rust’s char type is four bytes in size and represents a Unicode Scalar Value,
        which means it can represent a lot more than just ASCII.
        Accented letters; Chinese, Japanese, and Korean characters; emoji;
        and zero-width spaces are all valid char values in Rust.
    */
    println!("\nCharacter Type\n");

    let c = 'z';
    let z: char = 'ℤ';
    // let z: char = 'ℤℤ';error: character literal may only contain one codepoint
    let heart_eyed_cat = '😻';
    let に = 'に';

    println!("The value of c is: {}", c);
    println!("The value of z is: {}", z);
    println!("The value of heart_eyed_cat is: {}", heart_eyed_cat);
    println!("The value of に is: {}", に);

    // Compound Types
    println!("\nCompound Types\n");

    /*
        Tuple Type
        ----------

        Tuple is a general way of grouping together a number of values with a variety of types
        into one compound type. Tuples have a fixed length: once declared, 
        they cannot grow or shrink in size.
    */

    let tup: (char, i32, f64) = ('あ', 0xFFFF, 3.14);
    let (a, b, c) = tup; // destructuring
    let hiragana_a = tup.0;
    let hex = tup.1;
    let pi = tup.2;

    let unit = (); // unit type

    println!("The value of a is: {}", a);
    println!("The value of b is: {}", b);
    println!("The value of c is: {}", c);
    println!("The value of hiragana_a is: {}", hiragana_a);
    println!("The value of hex is: {}", hex);
    println!("The value of pi is: {}", pi);
    println!("The value of unit is: {:?}", unit);

    /*
        Array Type
        ----------

        Unlike a tuple, every element of an array must have the same type.
        Unlike arrays in some other languages, arrays in Rust have a fixed length.
    */
    println!("\nArray Type\n");

    let array: [i32; 5] = [1, 2, 3, 4, 5];
    let mut ram_6502: [u8; 0x10000] = [0; 0x10000]; // 0x10000 = 65536 = 2^16 = 64KB

    println!("The 4th element of array is: {}", array[3]);
    println!("The 0th element of ram_6502 is: {}", ram_6502[0]);
    println!("The 0xFFFFth element of ram_6502 is: {}", ram_6502[0xFFFF]);
    let mut register_x: u8;
    println!("ldx #$B1");
    register_x = 0xB1;
    println!("The value of register_x is: {}", register_x);
    println!("stx $FC"); // zero page
    ram_6502[0xFC] = register_x;
    println!("The value of ram_6502[0xFC] is: {}", ram_6502[0xFC]);
    println!("inx");
    register_x += 1;
    println!("The value of register_x is: {}", register_x);
    println!("stx $FD"); // zero page
    ram_6502[0xFD] = register_x;
    println!("The value of ram_6502[0xFD] is: {}", ram_6502[0xFD]);


    /*
        Functions
        ---------

        Functions are declared using the fn keyword and their name, 
        they can have parameters and a return value, 
        and they contain some code that is run when the function is called from somewhere else.
    */
    println!("\nFunctions\n");

    let _a_in_hira = a_in_hiragana();
    let mut fib_10: [u128; 10] = [0; 10];
    const L: usize = 186;
    let mut fib_l: [u128; L] = [0; L];

    fibonacci(&mut fib_10);
    fibonacci(&mut fib_l);

    println!("The value of _a_in_hira is: {}", _a_in_hira);
    println!("The value of fib_10 is: {:?}", fib_10);
    println!("The value of fib_l is: {:?}", fib_l);

    /*
        Comments
        --------

        Single line comments start with two slashes (//) and continue until the end of the line.
        Multi-line comments start with /* and end with */.
    */
    println!("\nComments\n");

    // This is a single line comment.
    /*
        This is a multi-line comment.
    */

    // println!("This line is commented out.");
    /*
        println!("This line is commented out too.")
    */

    /*
        Control Flow
        ------------
    */
    println!("\nControl Flow\n");

    // if expressions
    println!("if expressions\n");

    if is_even(123) {
        println!("123 is even.");
    } else {
        println!("123 is odd.");
    }

    // if 1 {...} -> eror[E0308]: mismatched types expected `bool`, found integer

    /*
        loop
        ----

        loop is a control flow construct that loops forever or until you explicitly tell it to stop.
    */
    println!("\nloop\n");

    let mut counter = 0;

    loop {
        counter += 1;
        println!("counter = {}", counter);
        if counter == 10 {
            break;
        }
    }
    

    // loop label
    println!("\nloop label\n");

    counter = 0;

    'outer: loop {
        println!("Entered the outer loop");
        println!("counter = {counter}");

        let mut remaining = 10;

        loop {
            println!("remaining = {remaining}");

            if remaining == 6 {
                break;
            }

            if counter == 4 {
                break 'outer;
            }

            remaining -= 1;
        }

        counter += 1;
    }

    println!("Exited the outer loop");

    // while
    println!("\nwhile\n");

    while counter != 0 {
        println!("counter = {}", counter);
        counter -= 1;
    }

    let arr = [10, 20, 30, 40, 50];
    
    let mut index = 0;

    while index < 5 {
        println!("the value is: {}", arr[index]);
        index += 1;
    }

    // for
    println!("\nfor\n");

    for element in arr.iter() {
        println!("the value is: {}", element);
    }

    println!("\nPoisson Distribution\n");
    println!("λ = .61; k = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10");

    for k in 0..11 {
        println!("P(X = {}) = {}", k, poisson(0.61, k));
    }

    println!();

    for number in (1..4).rev() {
        println!("{number}!");
    }

    println!("LIFTOFF!!!");
}
