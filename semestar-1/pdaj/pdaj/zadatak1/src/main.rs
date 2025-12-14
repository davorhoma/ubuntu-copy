fn main() {
    println!("Hello, world!");

    let tempF: f64 = 100.0;

    println!("Rez: {}", convert(tempF));
}

fn convert(tempF: f64) -> f64 {
    (tempF - 32.0) / (9.0/5.0)
}
