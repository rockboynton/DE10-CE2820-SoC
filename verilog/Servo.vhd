-- Name: Draven Schilling
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Servo Implementation
-- 3/20/19

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Servo is
port(
		CLK, RST: in std_logic;
		DB : in std_logic_vector(7 downto 0);
		PULSEOUT: out std_logic
	);
end entity Servo;
--clock and reset provided by system
--DB is the input data 0-255 for setting the position of the servo
--pulseout is the output signal for the servo pwm

architecture BEHAV of Servo is

--create state machine and free running counter of 20ms to manage states
	type state is(ONN, OFF);
	signal COUNT : unsigned(19 downto 0);
	signal CS, NS : state := ONN;

begin

--update free running counter
	process(CLK, RST) is
	begin
		if(RST='1') then
			COUNT <= (others => '0');
		elsif rising_edge(CLK) then
			if (COUNT = 1000000) then
				COUNT <= (others => '0');
			else
				COUNT <= COUNT + 1;
			end if;
		end if;
		CS <= NS;
	end process;
	
-- determine what the next state will be
	NSL: process(COUNT) is
	begin
		case CS is
		--turn off the signal if input is greater than 200 or if the pulse duration is done
			when ONN =>
				if(unsigned(DB) >200) then
					NS <= OFF;
				elsif(COUNT = (to_integer(unsigned(DB)*255)+50000)) then
					NS <= OFF;
				else 
					NS <= ONN;
				end if;
			when OFF =>
			--turn the signal on after the 20ms counter reset's
				if(unsigned(DB) >200) then
					NS <= OFF;
				elsif(COUNT = 1000000) then
					NS <= ONN;
				else
					NS <= OFF;
				end if;
			when others => NS <= OFF;
		end case;
	end process NSL;
	PULSEOUT <= '1' when CS = ONN else '0';

end architecture BEHAV;




