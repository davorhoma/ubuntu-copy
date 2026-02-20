fn main() {
    let v1 = vec![1, 2, 3];

    for val in &v1 {
        println!("Got: {val}");
    }

    let v1_iter = v1.iter();


    for val in v1_iter {
        println!("Got: {val}");
    }
}