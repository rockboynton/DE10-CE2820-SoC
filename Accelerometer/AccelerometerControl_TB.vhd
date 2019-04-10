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
            -- begin XHIGHER transmission of test value "0b1010_1010", CS should be low
            '1' after 1660ns, -- D7
            -- each subsequent bit is on the next clock edge
            '0' after 1860ns, -- D6
            '1' after 2060ns, -- D5
            '0' after 2260ns, -- D4
            '1' after 2460ns, -- D3
            '0' after 2660ns, -- D2
            '1' after 2860ns, -- D1
            '0' after 3060ns, -- D0

            -- begin XLOWER transmission of test value "0b0101_0101"
            '0' after 3260ns, -- D7
            -- each subsequent bit is on the next clock edge
            '1' after 3460ns, -- D6
            '0' after 3660ns, -- D5
            '1' after 3860ns, -- D4
            '0' after 4060ns, -- D3
            '1' after 4260ns, -- D2
            '0' after 4460ns, -- D1
            '1' after 4660ns, -- D0

            -- begin YHIGHER transmission of test value "0b1111_1111", CS should be low
            '1' after 4860ns, -- D7
            -- each subsequent bit is on the next clock edge
            '1' after 5060ns, -- D6
            '1' after 5260ns, -- D5
            '1' after 5460ns, -- D4
            '1' after 5660ns, -- D3
            '1' after 5860ns, -- D2
            '1' after 6060ns, -- D1
            '1' after 6260ns, -- D0

            -- begin YLOWER transmission of test value "0b0000_0000", CS should be low
            '0' after 6460ns, -- D7
            -- each subsequent bit is on the next clock edge
            '0' after 6660ns, -- D6
            '0' after 6860ns, -- D5
            '0' after 7060ns, -- D4
            '0' after 7260ns, -- D3
            '0' after 7460ns, -- D2
            '0' after 7660ns, -- D1
            '0' after 7860ns, -- D0

            -- begin ZHIGHER transmission of test value "01111_0000", CS should be low
            '1' after 8060ns, -- D7
            -- each subsequent bit is on the next clock edge
            '1' after 8260ns, -- D6
            '1' after 8460ns, -- D5
            '1' after 8660ns, -- D4
            '0' after 8860ns, -- D3
            '0' after 9060ns, -- D2
            '0' after 9260ns, -- D1
            '0' after 9460ns, -- D0

            -- begin ZLOWER transmission of test value "0b0000_1111", CS should be low
            '0' after 9660ns, -- D7
            -- each subsequent bit is on the next clock edge
            '0' after 9860ns, -- D6
            '0' after 10060ns, -- D5
            '0' after 10260ns, -- D4
            '1' after 10460ns, -- D3
            '1' after 10660ns, -- D2
            '1' after 10860ns, -- D1
            '1' after 11060ns, -- D0

            -- CS should now return high
        wait;
    end process tester;

end architecture TESTBENCH;
