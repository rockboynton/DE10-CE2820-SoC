	component Computer_System is
		port (
			acceleromter_control_I2C_SDAT      : inout std_logic                     := 'X';             -- I2C_SDAT
			acceleromter_control_I2C_SCLK      : out   std_logic;                                        -- I2C_SCLK
			acceleromter_control_G_SENSOR_CS_N : out   std_logic;                                        -- G_SENSOR_CS_N
			acceleromter_control_G_SENSOR_INT  : in    std_logic                     := 'X';             -- G_SENSOR_INT
			arduino_gpio_export                : inout std_logic_vector(15 downto 0) := (others => 'X'); -- export
			arduino_reset_n_export             : out   std_logic;                                        -- export
			expansion_jp1_export               : inout std_logic_vector(31 downto 0) := (others => 'X'); -- export
			hex3_hex0_export                   : out   std_logic_vector(31 downto 0);                    -- export
			hex5_hex4_export                   : out   std_logic_vector(15 downto 0);                    -- export
			leds_export                        : out   std_logic_vector(9 downto 0);                     -- export
			pushbuttons_export                 : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			sdram_addr                         : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_ba                           : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n                        : out   std_logic;                                        -- cas_n
			sdram_cke                          : out   std_logic;                                        -- cke
			sdram_cs_n                         : out   std_logic;                                        -- cs_n
			sdram_dq                           : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_dqm                          : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_ras_n                        : out   std_logic;                                        -- ras_n
			sdram_we_n                         : out   std_logic;                                        -- we_n
			sdram_clk_clk                      : out   std_logic;                                        -- clk
			servo_1_control_export             : out   std_logic_vector(7 downto 0);                     -- export
			servo_2_control_export             : out   std_logic_vector(7 downto 0);                     -- export
			slider_switches_export             : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			system_pll_ref_clk_clk             : in    std_logic                     := 'X';             -- clk
			system_pll_ref_reset_reset         : in    std_logic                     := 'X';             -- reset
			camera_control_sda_in              : in    std_logic                     := 'X';             -- sda_in
			camera_control_scl_in              : in    std_logic                     := 'X';             -- scl_in
			camera_control_sda_oe              : out   std_logic;                                        -- sda_oe
			camera_control_scl_oe              : out   std_logic                                         -- scl_oe
		);
	end component Computer_System;

	u0 : component Computer_System
		port map (
			acceleromter_control_I2C_SDAT      => CONNECTED_TO_acceleromter_control_I2C_SDAT,      -- acceleromter_control.I2C_SDAT
			acceleromter_control_I2C_SCLK      => CONNECTED_TO_acceleromter_control_I2C_SCLK,      --                     .I2C_SCLK
			acceleromter_control_G_SENSOR_CS_N => CONNECTED_TO_acceleromter_control_G_SENSOR_CS_N, --                     .G_SENSOR_CS_N
			acceleromter_control_G_SENSOR_INT  => CONNECTED_TO_acceleromter_control_G_SENSOR_INT,  --                     .G_SENSOR_INT
			arduino_gpio_export                => CONNECTED_TO_arduino_gpio_export,                --         arduino_gpio.export
			arduino_reset_n_export             => CONNECTED_TO_arduino_reset_n_export,             --      arduino_reset_n.export
			expansion_jp1_export               => CONNECTED_TO_expansion_jp1_export,               --        expansion_jp1.export
			hex3_hex0_export                   => CONNECTED_TO_hex3_hex0_export,                   --            hex3_hex0.export
			hex5_hex4_export                   => CONNECTED_TO_hex5_hex4_export,                   --            hex5_hex4.export
			leds_export                        => CONNECTED_TO_leds_export,                        --                 leds.export
			pushbuttons_export                 => CONNECTED_TO_pushbuttons_export,                 --          pushbuttons.export
			sdram_addr                         => CONNECTED_TO_sdram_addr,                         --                sdram.addr
			sdram_ba                           => CONNECTED_TO_sdram_ba,                           --                     .ba
			sdram_cas_n                        => CONNECTED_TO_sdram_cas_n,                        --                     .cas_n
			sdram_cke                          => CONNECTED_TO_sdram_cke,                          --                     .cke
			sdram_cs_n                         => CONNECTED_TO_sdram_cs_n,                         --                     .cs_n
			sdram_dq                           => CONNECTED_TO_sdram_dq,                           --                     .dq
			sdram_dqm                          => CONNECTED_TO_sdram_dqm,                          --                     .dqm
			sdram_ras_n                        => CONNECTED_TO_sdram_ras_n,                        --                     .ras_n
			sdram_we_n                         => CONNECTED_TO_sdram_we_n,                         --                     .we_n
			sdram_clk_clk                      => CONNECTED_TO_sdram_clk_clk,                      --            sdram_clk.clk
			servo_1_control_export             => CONNECTED_TO_servo_1_control_export,             --      servo_1_control.export
			servo_2_control_export             => CONNECTED_TO_servo_2_control_export,             --      servo_2_control.export
			slider_switches_export             => CONNECTED_TO_slider_switches_export,             --      slider_switches.export
			system_pll_ref_clk_clk             => CONNECTED_TO_system_pll_ref_clk_clk,             --   system_pll_ref_clk.clk
			system_pll_ref_reset_reset         => CONNECTED_TO_system_pll_ref_reset_reset,         -- system_pll_ref_reset.reset
			camera_control_sda_in              => CONNECTED_TO_camera_control_sda_in,              --       camera_control.sda_in
			camera_control_scl_in              => CONNECTED_TO_camera_control_scl_in,              --                     .scl_in
			camera_control_sda_oe              => CONNECTED_TO_camera_control_sda_oe,              --                     .sda_oe
			camera_control_scl_oe              => CONNECTED_TO_camera_control_scl_oe               --                     .scl_oe
		);

