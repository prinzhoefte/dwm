use std::process::Command;

pub struct Battery {
    pub battery_percentage: f64,
    pub battery_status: String,
}

impl Battery {
    pub fn new() -> Battery {
        Battery {
            battery_percentage: 0.0,
            battery_status: String::new(),
        }
    }

    pub fn read_battery_percentage(&mut self) {
        let output = Command::new("acpi")
            .arg("-b")
            .output()
            .expect("Failed to execute acpi command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            if line.contains("Battery 0") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                let percentage: Vec<&str> = parts[3].split("%").collect();
                self.battery_percentage = percentage[0].parse().unwrap_or(0.0);
                return;
            }
        }
    }

    pub fn read_battery_status(&mut self) {
        let output = Command::new("acpi")
            .arg("-b")
            .output()
            .expect("Failed to execute acpi command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            if line.contains("Battery 0") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                self.battery_status = parts[2].to_string().replace(",", "");
                return;
            }
        }
    }
}
