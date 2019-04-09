-- Name: Rock Boynton
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Accelerometer Control Testbench
-- 4/8/19

library ieee;
use ieee.std_logic_1164.all;

entity AccelerometerControl_TB is
end entity AccelerometerControl_TB;

architecture TESTBENCH of AccelerometerControl_TB is

	component AccelerometerControl is
	port(
        CLK, MDI, RST    : in std_logic;
        CS , MDO, CLKOUT : out std_logic;
        X  , Y  , Z      : out std_logic_vector(9 downto 0)
		);
	end component AccelerometerControl;

	--create signals for each pin in the input/outputs
    signal CLK    : std_logic : = '0';
    signal MDI    : std_logic : = '0';
    signal RST    : std_logic : = '0';
    signal CS     : std_logic : = '0';
    signal MDO    : std_logic : = '0';
    signal CLKOUT : std_logic : = '0';
    signal X      : std_logic_vector(9 downto 0);
    signal Y      : std_logic_vector(9 downto 0);
    signal Z      : std_logic_vector(9 downto 0);

begin

    UUT: AccelerometerControl port map(
        CLK=>CLK,
        MDI=>MDI,
        RST=>RST,
        CS=>CS,
        MDO=>MDO,
        CLKOUT=>CLKOUT,
        X=>X,
        Y=>Y,
        Z=>Z
    );

    -- continuous 50MHz clock  (System clock)
    clock: process
    begin
        CLK <= '0';
        wait for 10ns;
        CLK <= '1';
        wait for 10ns;
    end process;

    tester: process
    begin
        -- test asynchronous, active low reset
        RST <= '0', '1' after 15ns;
        -- test accelerometer
        -- Calculations: (pg. 15 & 16)
        -- t_sclk == 200ns,
        -- t_delay == 5ns,
        -- t_sdo == 40ns,
        -- need to wait RST test time + t_delay + t_sclk + t_sdo + 7(t_sclk)
        -- == 1660ns
        MDI <= '0',
            -- begin transmission of test value "0b1010_1010", CS should be low
            '1' after 1660ns, -- D7
            -- each subsequent bit is on the next clock edge (Draven: which clock edge?)
				-- rock: data is updated on the falling edge of the clock and is sampled on the rising edge. so i think this is right?
            '1' after 1860ns, -- D6
            '0' after 2060ns, -- D5
            '1' after 2260ns, -- D4
            '0' after 2460ns, -- D3
            '1' after 2860ns, -- D2
            '0' after 3060ns, -- D1
            '0' after 3260ns, -- D0
				--rock: repeat d7-d0 5 more times, then cs should go high. also try different inputs '1''s '0''s to distinguish that it's acutually reading.
            -- CS should now return high
        wait;
    end process tester;

end architecture TESTBENCH;
