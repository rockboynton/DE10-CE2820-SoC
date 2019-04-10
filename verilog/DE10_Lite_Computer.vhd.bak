library ieee;
use ieee.std_logic_1164.all;

entity DE10_Lite_Computer is
port(
		-- Clock pins
		CLOCK_50 : in std_logic;
		CLOCK2_50 : in std_logic;
		CLOCK_ADC_10 : in std_logic;

		-- ARDUINO
		ARDUINO_IO : inout std_logic_vector(15 downto 0);
		ARDUINO_RESET_N : inout std_logic;
			
		-- SDRAM
		DRAM_ADDR : out std_logic_vector(12 downto 0);
		DRAM_BA : out std_logic_vector(1 downto 0);
		DRAM_CAS_N : out std_logic;
		DRAM_CKE : out std_logic;
		DRAM_CLK : out std_logic;
		DRAM_CS_N : out std_logic;
		DRAM_DQ : inout std_logic_vector(15 downto 0);
		DRAM_LDQM : out std_logic;
		DRAM_RAS_N : out std_logic;
		DRAM_UDQM : out std_logic;
		DRAM_WE_N : out std_logic;

		-- Accelerometer
		G_SENSOR_CS_N : out std_logic;
		G_SENSOR_INT : in std_logic_vector(2 downto 1);
		G_SENSOR_SCLK : out std_logic;
		G_SENSOR_SDI : inout std_logic;
		G_SENSOR_SDO : inout std_logic;
			
		-- 40-pin headers
		GPIO : inout std_logic_vector(35 downto 0);

		-- Seven Segment Displays
		HEX0 : out std_logic_vector(7 downto 0);
		HEX1 : out std_logic_vector(7 downto 0);
		HEX2 : out std_logic_vector(7 downto 0);
		HEX3 : out std_logic_vector(7 downto 0);
		HEX4 : out std_logic_vector(7 downto 0);
		HEX5 : out std_logic_vector(7 downto 0);

		-- Pushbuttons
		KEY : in std_logic_vector(1 downto 0);

		-- LEDs
		LEDR : out std_logic_vector(9 downto 0);

		-- Slider Switches
		SW : in std_logic_vector(9 downto 0);

		-- VGA
		VGA_B : out std_logic_vector(3 downto 0);
		VGA_G : out std_logic_vector(3 downto 0);
		VGA_HS : out std_logic;
		VGA_R : out std_logic_vector(3 downto 0);
		VGA_VS : out std_logic
		
		
		
		);
end entity DE10_Lite_Computer;


architecture Structural of DE10_Lite_Computer is

	component Computer_System is
        port (
            arduino_gpio_export        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- export
            arduino_reset_n_export     : out   std_logic;                                        -- export
            expansion_jp1_export       : inout std_logic_vector(31 downto 0) := (others => 'X'); -- export
            hex3_hex0_export           : out   std_logic_vector(31 downto 0);                    -- export
            hex5_hex4_export           : out   std_logic_vector(15 downto 0);                    -- export
            leds_export                : out   std_logic_vector(9 downto 0);                     -- export
            pushbuttons_export         : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
            sdram_addr                 : out   std_logic_vector(12 downto 0);                    -- addr
            sdram_ba                   : out   std_logic_vector(1 downto 0);                     -- ba
            sdram_cas_n                : out   std_logic;                                        -- cas_n
            sdram_cke                  : out   std_logic;                                        -- cke
            sdram_cs_n                 : out   std_logic;                                        -- cs_n
            sdram_dq                   : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
            sdram_dqm                  : out   std_logic_vector(1 downto 0);                     -- dqm
            sdram_ras_n                : out   std_logic;                                        -- ras_n
            sdram_we_n                 : out   std_logic;                                        -- we_n
				sdram_clk_clk					: out   std_logic;
            slider_switches_export     : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
            system_pll_ref_clk_clk     : in    std_logic                     := 'X';             -- clk
            system_pll_ref_reset_reset : in    std_logic                     := 'X';              -- reset
				
				servo_1_control_export            : out   std_logic_vector(7 downto 0);                     -- export
            servo_2_control_export            : out   std_logic_vector(7 downto 0)                      -- export
				
        );
    end component Computer_System;
	 
	signal hex3_hex0 : std_logic_vector(31 downto 0);
	signal hex5_hex4 : std_logic_vector(15 downto 0);
	
	signal jp1_export : std_logic_vector(31 downto 0);
	signal keys : std_logic_vector(1 downto 0);
	signal dqm : std_logic_vector(1 downto 0);
	
	component Servo is
	port(
			CLK, RST: in std_logic;
			DB : in std_logic_vector(7 downto 0);
			PULSEOUT: out std_logic
		);
	end component Servo;
	
	signal servo1_data : std_logic_vector(7 downto 0);
	signal servo2_data : std_logic_vector(7 downto 0);

begin
	u0 : component Computer_System
        port map (
            arduino_gpio_export        => open,        --         arduino_gpio.export
            arduino_reset_n_export     => ARDUINO_RESET_N,     --      arduino_reset_n.export
            expansion_jp1_export       => jp1_export,       --        expansion_jp1.export
            hex3_hex0_export           => hex3_hex0,           --            hex3_hex0.export
            hex5_hex4_export           => hex5_hex4,           --            hex5_hex4.export
            leds_export                => LEDR,                --                 leds.export
            pushbuttons_export         => keys,         --          pushbuttons.export
            sdram_addr                 => DRAM_ADDR,                 --                sdram.addr
            sdram_ba                   => DRAM_BA,                   --                     .ba
            sdram_cas_n                => DRAM_CAS_N,                --                     .cas_n
            sdram_cke                  => DRAM_CKE,                  --                     .cke
            sdram_cs_n                 => DRAM_CS_N,                 --                     .cs_n
            sdram_dq                   => DRAM_DQ,                   --                     .dq
            sdram_dqm                  => dqm,                  --                     .dqm
            sdram_ras_n                => DRAM_RAS_N,                --                     .ras_n
            sdram_we_n                 => DRAM_WE_N,                 --                     .we_n
				sdram_clk_clk					=> DRAM_CLK,
            slider_switches_export     => SW,     --      slider_switches.export
            system_pll_ref_clk_clk     => CLOCK_50,     --   system_pll_ref_clk.clk
            system_pll_ref_reset_reset => '0',  -- system_pll_ref_reset.reset
				
				servo_1_control_export            => servo1_data,            --            servo1_pw.export
            servo_2_control_export            => servo2_data             --            servo2_pw.export
        );
		  
		  
			HEX0 <= not hex3_hex0(7 downto 0);
			HEX1 <= not hex3_hex0(15 downto 8);
			HEX2 <= not hex3_hex0(23 downto 16);
			HEX3 <= not hex3_hex0(31 downto 24);
			HEX4 <= not hex5_hex4(7 downto 0);
			HEX5 <= not hex5_hex4(15 downto 8);

			GPIO(0) <= jp1_export(0);
			GPIO(15 downto 3) <= jp1_export(13 downto 1);
			GPIO(17) <= jp1_export(14);
			GPIO(35 downto 19) <= jp1_export(31 downto 15);
			
			keys <= not KEY;
			
			DRAM_UDQM <= dqm(1);
			DRAM_LDQM <= dqm(0);
			
			servo1: component Servo
				port map(
					CLK => CLOCK_50,
					RST => '0',
					DB => servo1_data,
					PULSEOUT =>ARDUINO_IO(9)
			);
			servo2: component Servo
				port map(
					CLK => CLOCK_50,
					RST => '0',
					DB => servo2_data,
					PULSEOUT =>ARDUINO_IO(10)
			);

end architecture;


