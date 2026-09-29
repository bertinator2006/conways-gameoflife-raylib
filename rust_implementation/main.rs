struct Number {
    odd: bool,
    value: i32,
}

// this is a void function
fn greet() {
    println!("Hi there!");
}

fn fair_dice_roll() -> i32 {
    return 4;
}

fn print_number(n: Number) {
    match n.value {
        1 => println!("One"),
        2 => println!("Two"),
        _ => println!("{}", n.value),
    }
}


fn main() {
    println!("Hello, world!");
    let x: i32;
    x = 42;

    let y: i32 = 67;
    //
    // this is how to throw away a value
    let _ = 42;

    let pair = ('a', 17);
    assert!(pair.0, 'a');
    assert!(pair.1, 17); // this is 17

    let pair2: (char, i32) = ('a', 17);

    let (some_char, some_int) = ('a', 17);
    assert!(some_char, 'a');
    assert!(some_int, 17);

    let j: Number = {odd: false, value:fair_dice_roll()};
    print_number(j);
    // let x = vec![1, 2, 3, 4, 5, 6, 7, 8]
    //     .iter()
    //     .map(|x| x + 3)
    //     .fold(0, |x, y| x + y);
}

