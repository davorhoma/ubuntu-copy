use std::io;

fn main() {
    // separate_string_to_vector();
    // obrni_elemente();
    zad5();
}

fn separate_string_to_vector() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Input a valid string");

    let vector: Vec<&str> = input.split(' ').collect();
    for val in &vector {
        println!("{:?}", val);
    }

    println!("{:?}", input);

    // let mut stringovi = Vec::<String>::new();
    // let bytes = input.as_bytes();
    // for val in bytes {
    //     println!("{}", *val);
    // }

    // println!("{:?}", stringovi);
}

fn obrni_elemente() {
    let mut input = String::new();
    println!("Input number of elements: ");
    std::io::stdin().read_line(&mut input).expect("Input a number!");
    let n: i32 = input.trim().parse().unwrap();
        
    let mut numbers: Vec<i32> = Vec::new();
    for i in 0..n {
        input.clear();
        println!("numbers[{}] = ", i);
        std::io::stdin().read_line(&mut input).expect("Input a number!");
        // let num: i32;
        match input.trim().parse() {
            Ok(val) => numbers.push(val),
            Err(_) => println!("ERROR parsing a value"),
        };
    }

    println!("Original:");
    for (i, val) in numbers.iter().enumerate() {
        println!("numbers[{}] = {}", i, val);
    }
    
    numbers.reverse();
    println!("Reversed:");
    for (i, val) in numbers.iter().enumerate() {
        println!("numbers[{}] = {}", i, val);
    }

    // let size = numbers.len();
    // for (i, val) in numbers.iter_mut().enumerate() {
    //     let temp = numbers[size - 1 - i];
    //     numbers[size - 1 - i] = *val;
    //     *val = temp;
    // }
    
}

fn zad5() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).expect("Input a valid string");
    input.pop();

    let mut counter: u32 = 0;
    let mut longestCounter: u32 = 0;
    let mut wordLength: Vec<u32> = Vec::new();
    let bytes = input.as_bytes();

    for (i, byte) in bytes.iter().enumerate() {
        if counter == 0 {
            if *byte != b' ' {
                longestCounter += 1;
                counter += 1;
                continue;
            }
        }

        if (*byte == b' ') && longestCounter > 0 {
            wordLength.push(longestCounter);
            longestCounter = 0;
        }

        if let Some(next) = bytes.get(i + 1) {
            if *byte == b' ' && *next != b' ' {
                counter += 1;
            } else if *byte != b' '{
                longestCounter += 1;
            }
        } else if *byte != b' ' {
            longestCounter += 1;
        }
    }

    if longestCounter > 0 {
        wordLength.push(longestCounter);
    }

    let words: Vec<&str> = input.split(' ').collect();
    
    if !words.is_empty() {
        let mut min: &str = words[0];
        let mut max: &str = words[0];
        let mut maxLen: usize = max.len();
        let mut minLen: usize = min.len();
        for word in words {
            if word.len() > maxLen {
                maxLen = word.len();
                max = word;
            }
    
            if word.len() > 0 && word.len() < minLen {
                minLen = word.len();
                min = word;
            }
        }

        println!("Longest word: {:?}, shortest word: {:?}", max, min);
    }

    println!("Broj reci u recenici je {}", counter);
    println!("Word lengths: {:?}", wordLength);

    // Is Palindrom

    println!("{:?}", input);
    let trimmed: String = input.to_lowercase().chars().filter(|c| !c.is_whitespace()).collect();
    let size = trimmed.len();
    let mut isPalindrom = true;

    let reversed: String = trimmed.chars().rev().collect();
    if trimmed == reversed {
        println!("Palindrom");
    } else {
        println!("Nije palindrom");
    }


    println!("{:?}", trimmed);
    println!("{:?}", reversed);
}