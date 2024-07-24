use sysinfo::System;

pub struct Memory {
    pub sys: System,
    pub memory_usage: f64,
    pub memory_total: f64,
}

impl Memory {
    pub fn new() -> Memory {
        Memory {
            sys: System::new(),
            memory_usage: 0.0,
            memory_total: 0.0,
        }
    }

    pub fn read_memory(&mut self) {
        self.sys.refresh_memory();
        self.memory_usage = self.sys.used_memory() as f64;
        self.memory_total = self.sys.total_memory() as f64;
    }
}
