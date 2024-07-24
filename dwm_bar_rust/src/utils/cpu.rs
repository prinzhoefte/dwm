use std::process::Command;
use sysinfo::System;

pub struct Cpu {
    pub cpu_usage: f64,
    pub cpu_temp: f64,
    pub sys: System,
}

impl Cpu {
    pub fn new() -> Cpu {
        Cpu {
            cpu_usage: 0.0,
            cpu_temp: 0.0,
            sys: System::new(),
        }
    }

    pub fn read_cpu_temps(&mut self) {
        let output = Command::new("sensors")
            .output()
            .expect("Failed to execute sensors command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            if line.contains("Package id 0:") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                for part in parts {
                    if part.contains("+") {
                        let temp: Vec<&str> = part.split("+").collect();
                        let temp: Vec<&str> = temp[1].split(".").collect();
                        self.cpu_temp = temp[0].parse().unwrap_or(0.0);
                        return;
                    }
                }
            }
        }
    }

    pub fn read_cpu_usage(&mut self) {
        self.sys.refresh_cpu();
        let mut avg_cpu_usage = 0.0;
        self.sys.cpus().iter().for_each(|cpu| {
            avg_cpu_usage += cpu.cpu_usage();
        });
        avg_cpu_usage /= self.sys.cpus().len() as f32;
        self.cpu_usage = avg_cpu_usage as f64;
    }
}
