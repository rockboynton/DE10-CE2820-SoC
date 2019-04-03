-- Name: Draven Schilling
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Servo Implementation
-- 3/20/19

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity AccelerometerControl is
port(
-- RST is active low
-- CS is active low
-- EN is active low
-- MDI = Master data in
-- MDO = Master data out
		CLK, MDI, RST, EN: in std_logic;
		CS, MDO: out std_logic;
		X, Y, Z: out std_logic_vector(9 downto 0);
	);
end entity AccelerometerControl;
--clock and reset provided by system
--DB is the input data 0-255 for setting the position of the servo
--pulseout is the output signal for the servo pwm

architecture BEHAV of AccelerometerControl is

--create state machine and free running counter of 20ms to manage states
	type state is(OFF, CSWAIT);
	signal COUNTPSC : unsigned(2 downto 0) := 0;
	signal AS, NS : state := OFF;
--AS = Active state
-- NS - Next state

begin

--update free running counter
	process(CLK, RST) is
	begin
		if(EN='0') then
			if(RST='0') then
				COUNT <= (others => '0');
				AS <= OFF;
				NS <= OFF;
			elsif rising_edge(CLK) then
				if (COUNT = 10) then
					COUNT <= (others => '0');
					AS <= NS;
				else
					COUNT <= COUNT + 1;
				end if;
			end if;
		else 
			AS <= OFF;
			NS <= OFF;
		end if;
		
	end process;
	
-- determine what the next state will be
	NSL: process(COUNT,EN) is
	begin
			case CS is
				when OFF =>
					if(CS = '0') then
						NS <= CSWAIT;
					else
						NS <= OFF;
					end if;
				when CSWAIT => NS <= ONN;
				
				when others => NS <= OFF;
			end case;
	end process NSL;
	
	PULSEOUT <= '1' when CS = ONN else '0';

end architecture BEHAV;




