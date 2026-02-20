use std::rc::Rc;
use std::cell::RefCell;

use crate::tasks::Task;

pub struct User {
    id: i32,
    name: String,
    tasks: Vec<Rc<RefCell<Task>>>
}

impl User {
    pub fn new(id: i32, name: String) -> Self {
        User {
            id: id,
            name: name,
            tasks: Vec::new()
        }
    }

    pub fn addTask(&mut self, task: Rc<RefCell<Task>>) {
        self.tasks.push(task);
    }

    pub fn print(&self) {
        println!("Korisnik: {}", self.name);
        for task in &self.tasks {
            task.borrow().print();
        }
    }
}