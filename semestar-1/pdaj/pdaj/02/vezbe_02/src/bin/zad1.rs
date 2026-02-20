use std::{collections::HashMap, io::{self, Read}};

fn main() {
    // f_to_c();
    // fibonacci_caller();
    // isNumberPrime();
    zadatak4();
    
    return;
}

fn f_to_c() {
    let mut input = String::new();
    println!("Input a number: ");
    io::stdin()
        .read_line(&mut input)
        .expect("Input a valid number");

    let temp_f = input.trim().parse::<f64>().unwrap();
    let temp_c = (temp_f - 32.0) * 5.0 / 9.0;

    println!(
        "Temperature in F: {},\nTemperature in C: {:.2}",
        temp_f, temp_c
    );
}

fn fibonacci_caller() {
    let mut input = String::new();
    println!("Input a number: ");
    std::io::stdin().read_line(&mut input).expect("Input a valid number");
    let n: i32 = input.trim().parse().unwrap();

    for i in 0..=n {
        let fib = fibonacci(i);
        println!("The {}. Fibonacci number is {}", i, fib);
    }

    // println!("The {}. Fibonacci number is: {}", n, fibonacci(n));
}

fn fibonacci(n: i32) -> i32 {
    if n <= 1 {
        return 1;
    }

    fibonacci(n - 1) + fibonacci(n - 2)
}

fn isNumberPrime() {
    println!("Input a number: ");

    let mut input = String::new();
    std::io::stdin().read_line(&mut input).expect("Input a valid number");
    let number: i32 = input.trim().parse().unwrap();

    let half = number / 2;

    let mut isPrime = true;
    for i in 2..=half {
        if number % i == 0 {
            // println!("Broj {} nije prost", number);
            isPrime = false;
            break;
        }
    }

    if isPrime {
        println!("Broj {} je prost.", number);
    } else {
        println!("Broj {} nije prost.", number);
    }
}

fn zadatak4() {
    println!("Input size of vector: ");
    
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).expect("Input a number!");
    
    let size: usize = input.trim().parse().unwrap();

    let mut vector: Vec<i32> = Vec::new();
    for i in 0..size {
        println!("vec[{}] = ", i);
        input = String::new();
        std::io::stdin().read_line(&mut input).expect("Input a number");
        println!("{}", input);
        let num: i32 = input.trim().parse().unwrap();

        vector.push(num);
    }

    for i in &vector {
        println!("Number {}", i);
    }

    for i in 0..size {
        if let Some(num) = vector.get(size - 1 - i) {
            println!("Number {}", num);
        }
    }

    input = String::new();
    println!("Input an index: ");
    std::io::stdin().read_line(&mut input).expect("Input a number");
    let index: usize = input.trim().parse().unwrap();
    if let Some(num) = vector.get(index) {
        println!("vector[{}] = {}", index, num);
    } else {
        println!("Index out of bounds");
    }

    for i in 0..size {
        if i % 3 == 0 {
            if let Some(num) = vector.get(i) {
                println!("vector[{}] = {}", i, num);
            }
        }
    }

    let mut evenOddCounter: HashMap<&str, i32> = HashMap::new();

    for i in 0..size {
        if let Some(_) = vector.get(i) {
            if i % 2 == 0 {
                let even = evenOddCounter.entry("even").or_insert(0);
                *even += 1;
            } else {
                let odd = evenOddCounter.entry("odd").or_insert(0);
                *odd += 1;
            }
        }
    }

    println!("evenOddCounter: {:?}", evenOddCounter);
}
