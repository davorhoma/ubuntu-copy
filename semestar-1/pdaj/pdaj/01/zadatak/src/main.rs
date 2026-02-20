fn main() {
    let mut sum: i128 = 0;
    for i in 0..10_000_00 {
        // println!("{}", i);
        sum += i;
    }

    println!("sum = {}", sum);
    println!("Hello, world!");
}
