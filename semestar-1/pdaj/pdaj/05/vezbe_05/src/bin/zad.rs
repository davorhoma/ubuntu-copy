struct Pair<'a, 'b> {
    first: &'a str,
    second: &'b i32
}

impl<'a, 'b> Pair<'a, 'b> {
    fn new(first: &'a str, second: &'b i32) -> Self {
        Self {
            first,
            second
        }
    }

    fn get_first(&self) -> &str {
        self.first
    }

    fn get_second(&self) -> &i32 {
        self.second
    }
}

trait Printable {
    fn print(&self);
}

struct Circle {
    radius: i32
}

struct Rectangle {
    width: i32,
    height: i32
}

impl Printable for Circle {
    fn print(&self) {
        println!("Circle has a radius of: {}", self.radius);
    }
}

impl Printable for Rectangle {
    fn print(&self) {
        println!("Rectangle: width = {}, height = {}", self.width, self.height);
    }
}

fn main() {
    let myPair = Pair::new("first", &32);

    println!("Get first: {}", myPair.get_first());
    println!("Get second: {}", myPair.get_second());

    let circle = Circle{ radius: 25 };
    let rectangle = Rectangle{ width: 25, height: 12 };

    circle.print();
    rectangle.print();
}