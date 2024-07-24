use std::process::Command;
use sysinfo::Networks;

pub struct Wifi {
    pub ssid: String,
    pub upload_speed: u64,
    pub download_speed: u64,
    pub networks: Networks,
}

impl Wifi {
    pub fn new() -> Wifi {
        Wifi {
            ssid: String::new(),
            upload_speed: 0,
            download_speed: 0,
            networks: Networks::new_with_refreshed_list(),
        }
    }

    pub fn get_current_wifi(&mut self) {
        let output = Command::new("iwgetid")
            .arg("-r")
            .output()
            .expect("Failed to execute iwgetid command");

        let output = String::from_utf8_lossy(&output.stdout);
        let lines: Vec<&str> = output.split('\n').collect();
        for line in lines {
            self.ssid = line.to_string();
            return;
        }
    }

    pub fn read_network_stats(&mut self) {
        self.networks.refresh();
        let mut combined_upload_speed = 0;
        let mut combined_download_speed = 0;
        for (interface_name, data) in &self.networks {
            if interface_name == "lo" {
                continue;
            }
            combined_upload_speed += data.transmitted();
            combined_download_speed += data.received();
        }
        self.upload_speed = combined_upload_speed;
        self.download_speed = combined_download_speed;
    }
}
