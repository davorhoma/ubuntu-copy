fn main() {
    println!("\n-------------------------- NIZ ------------------------------");
    niz();

    println!("\n-------------------------- VECTOR ------------------------------");
    mut_v();
    
    println!("\n-------------------------- PRINT VECTOR ------------------------------");
    let v = vec![0, 2, 16, 5];
    print_v(&v);

    println!("\n-------------------------- PRINT SORTED VECTOR ------------------------------");
    let mut mutable_v = v;
    mutable_v.sort();
    print_v(&mutable_v);

    print_v(&mutable_v[0..2]);
}

fn niz() {
    let mut sieve = [true; 10_000];
    for i in 2..100 {
        if sieve[i] {
            let mut j = i * i;
            while j < 10_000 {
                sieve[j] = false;
                j += i;
            }
        }
    }

    println!("sieve[211]: {}", sieve[211]);
    println!("sieve[9876]: {}", sieve[9876]);
    println!("sieve: {:?}", sieve);

    let mut trues: u32 = 0;
    let mut falses: u32 = 0;
    for i in 0..10_000 {
        if sieve[i] == true {
            trues += 1;
        } else {
            falses += 1;
        }
    }

    println!("trues: {}", trues);
    println!("falses: {}", falses);

    assert!(sieve[211]);
    assert!(!sieve[9876]);
}

fn mut_v() {
    let mut v = Vec::new();

    v.push(5);
    v.push(6);
    v.push(7);
    v.push(8);

    println!("v: {:?}", v);
}

fn print_v(v: &[i32]) {
    for el in v {
        print!("{}, ", el);
    }

    print!("\n");
}