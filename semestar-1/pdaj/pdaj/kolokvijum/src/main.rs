use std::rc::Rc;
use std::cell::RefCell;

#[derive(Debug, Clone)]
enum State {
    Incomplete,
    InProgress,
    Complete
}

#[derive(Debug, Clone)]
struct Task {
    id: i32,
    name: String,
    state: State,
    note: Option<String>,
}

impl Task {
    fn new(id: i32, name: String) -> Self {
        Task {
            id: id,
            name: name,
            state: State::Incomplete,
            note: None
        }
    }

    fn startTask(&mut self) {
        self.state = State::InProgress;
    }

    fn finishTask(&mut self, note: Option<String>) {
        self.state = State::Complete;
        self.note = note;
    }

    fn print(&self) {
        println!("Task: {}, {:?}, {:?}, {:?}", self.id, self.name, self.state, self.note);
    }
}

struct Project {
    id: i32,
    name: String,
    tasks: Vec<Rc<RefCell<Task>>>,
}

impl Project {
    fn new(id: i32, name: String) -> Self {
        Project {
            id: id,
            name: name,
            tasks: vec![],
        }
    }

    fn addTask(&mut self, task: Rc<RefCell<Task>>) {
        self.tasks.push(task);
    }

    fn print(&self) {
        println!("Projekat: {:?}", self.name);
        for (i, task) in self.tasks.iter().enumerate() {
            println!("Zadatak {}: {:?}", i, task);
        }
    }
}

struct User {
    id: i32,
    name: String,
    tasks: Vec<Rc<RefCell<Task>>>,
}

impl User {
    fn new(id: i32, name: String) -> Self {
        User {
            id: id,
            name: name,
            tasks: vec![],
        }
    }

    fn addTask(&mut self, task: Rc<RefCell<Task>>) {
        self.tasks.push(task);
    }

    fn print(&self) {
        println!("Korisnik: {:?}", self.name);
        for (i, task) in self.tasks.iter().enumerate() {
            println!("Task {}: {:?}", i, task);
        }
    }
}

fn main() {
    println!("Hello, world!");

    let mut task = Rc::new(RefCell::new(Task::new(32, String::from("Dizajn interfejsa"))));
    // task.print();

    let mut project = Project::new(11, String::from("Projekat Alfa"));
    project.addTask(Rc::clone(&task));
    let task2 = Rc::new(RefCell::new(Task::new(88, String::from("Implementacija pozadine"))));
    project.addTask(Rc::clone(&task2));
    project.print();

    let mut user = User::new(5, String::from("Ana"));
    user.addTask(Rc::clone(&task));

    println!("\n\n-----------------");
    println!("Pre zapocinjanja zadataka");
    task.borrow().print();
    println!("");
    project.print();
    println!("");
    user.print();
    
    task.borrow_mut().finishTask(Some(String::from("Verzija 1 završena.")));
    println!("\n\n-----------------");
    println!("After finishing: ");
    task.borrow().print();
    println!("");
    project.print();
    println!("");
    user.print();
}
