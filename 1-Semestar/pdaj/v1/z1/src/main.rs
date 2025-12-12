fn main() {
    println!("Hello, world!");

    z1();
}

fn z1() {
    let mut sum: u64 = 0;

    for i in 1..=10_000_000 {
        sum += i;
    }

    println!("sum = {}", sum);
}