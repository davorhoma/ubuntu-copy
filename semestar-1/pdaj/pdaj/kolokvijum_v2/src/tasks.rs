pub enum State {
    Incomplete,
    InProgress,
    Complete(String),
}

pub struct Task {
    pub id: i32,
    pub name: String,
    pub state: State,
}

impl Task {
    pub fn new(id: i32, name: String) -> Self {
        Task {
            id: id,
            name: name,
            state: State::Incomplete,
        }
    }

    pub fn startTask(&mut self) {
        self.state = State::InProgress;
    }

    pub fn finishTask(&mut self, note: String) {
        self.state = State::Complete(note);
    }

    pub fn print(&self) {
        match &self.state {
            State::Incomplete => println!("- Zadatak: {}, Stanje: Incomplete", self.name),
            State::InProgress => println!("- Zadatak: {}, Stanje: InProgress", self.name),
            State::Complete(note) => println!("- Zadatak: {}, Stanje: Complete (Beleska: {})", self.name, note),
        }
    }
}