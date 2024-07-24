/*

    Author: Justin Kosten
    Description: DWM Bar to replace the C alternative

*/

use std::thread::sleep;

mod models;
mod utils;

use utils::battery::Battery;
use utils::cpu::Cpu;
use utils::memory::Memory;
use utils::time::Time;
use utils::wifi::Wifi;

fn main() {
    let mut wifi = Wifi::new();
    let mut cpu = Cpu::new();
    let mut battery = Battery::new();
    let mut memory = Memory::new();
    let mut time = Time::new();
    let mut battery_icon;
    loop {
        wifi.get_current_wifi();
        wifi.read_network_stats();
        cpu.read_cpu_temps();
        cpu.read_cpu_usage();
        battery.read_battery_percentage();
        battery.read_battery_status();
        memory.read_memory();
        time.read_time();
        time.read_date();

        battery_icon = match battery.battery_status.as_str() {
            "Discharging" => match battery.battery_percentage {
                0.0..=10.0 => "",
                10.0..=25.0 => "",
                25.0..=50.0 => "",
                50.0..=75.0 => "",
                75.0..=100.0 => "",
                _ => "",
            },
            "Charging" => "",
            "Full" => "",
            _ => "",
        };

        std::process::Command::new("xsetroot")
            .arg("-name")
            .arg(&format!(
                "[ {}  {:.2}MB/s  {:.2}MB/s] [ {:.1}%] [ {:.1}GB] [ {}C] [{} {}%] [ {} {}]",
                wifi.ssid,
                (wifi.download_speed as f64) / 1024.0 / 1024.0,
                (wifi.upload_speed as f64) / 1024.0 / 1024.0,
                cpu.cpu_usage,
                (memory.memory_usage / 1024.0 / 1024.0 / 1024.0),
                cpu.cpu_temp,
                battery_icon,
                battery.battery_percentage,
                time.date,
                time.time
            ))
            .output()
            .expect("Failed to execute xsetroot command");

        sleep(std::time::Duration::from_secs(1));
    }
}
