use std::process::Command;

pub struct Time {
    pub time: String,
    pub date: String,
}

impl Time {
    pub fn new() -> Time {
        Time {
            time: String::new(),
            date: String::new(),
        }
    }

    pub fn read_time(&mut self) {
        let output = Command::new("date")
            .arg(&"+%T")
            .output()
            .expect("Failed to execute date command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            self.time = line.to_string();
            return;
        }
    }

    pub fn read_date(&mut self) {
        let output = Command::new("date")
            .arg(&"+%d-%m")
            .output()
            .expect("Failed to execute date command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            self.date = line.to_string();
            return;
        }
    }
}
