-- Name: Draven Schilling
-- Course: CE 2820
-- Teacher: Dr. Livingston
-- Lab 3 Accelerometer Control Implementation
-- 3/20/19

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- RST is processor provided active low
-- MDI = Master data in
-- MDO = Master data out
-- CS = chip select to accelerometer periphrial
-- X,Y,Z output values for the corosponding componenents of the accelerometer
-- CLKOUT = slow clock used to drive the slaver periphrial
entity AccelerometerControl is
port(
		CLK, MDI, RST: in std_logic;
		CS, MDO, CLKOUT: out std_logic;
		X, Y, Z: out std_logic_vector(9 downto 0)
	);
end entity AccelerometerControl;

architecture BEHAV of AccelerometerControl is

--create state machine AS is active state, NS is next state
	type state is(OFF,CSWAIT,READB,MULB,A0,A1,A2,A3,A4,A5,D0,D1,D2,D3,D4,D5,D6,D7,CSDIS);
	signal AS, NS : state := OFF;

--prescaling counter that ideally makes the clock 10 times slower. falling edge at 0 and rising edge at 4. reset at 10
-- supposed to create slow clock period of 200ns
	signal COUNT : integer range 0 to 10 := 0;
--counter which manages reading 6 data bytes from the XLower base address
	signal DATACOUNT : integer range 0 to 6 := 0;

--intermediate signals for the X,Y,Z output signals
	signal XLOWER :std_logic_vector(9 downto 0) := "0000000000";
	signal YLOWER :std_logic_vector(9 downto 0) := "0000000000";
	signal ZLOWER :std_logic_vector(9 downto 0) := "0000000000";


begin

--master counter
-- creates slave clock and manages the state machine
	process(CLK, RST) is
	begin
		if(RST='0') then
			COUNT <= 0;
			AS <= OFF;
		elsif rising_edge(CLK) then
			if (COUNT = 10) then
				COUNT <= 0;
				--update falling edge of synthetic clock
				CLKOUT <= '0';
				--change state on falling edge
				AS <= NS;
			elsif (COUNT = 4) then
				--update rising edge of synthetic clock and increment counter
				CLKOUT <= '1';
				COUNT <= COUNT + 1;
				--create logic for getting data from accelerometer if appropriate
				if(DATACOUNT = 0) then
					if(AS = D0) then
						XLOWER(0) <= MDI;
					elsif(AS = D1) then
						XLOWER(1) <= MDI;
					elsif(AS = D2) then
						XLOWER(2) <= MDI;
					elsif(AS = D3) then
						XLOWER(3) <= MDI;
					elsif(AS = D4) then
						XLOWER(4) <= MDI;
					elsif(AS = D5) then
						XLOWER(5) <= MDI;
					elsif(AS = D6) then
						XLOWER(6) <= MDI;
					elsif(AS = D7) then
						XLOWER(7) <= MDI;
					end if;
				elsif(DATACOUNT = 1) then
					if(AS = D0) then
						XLOWER(8) <= MDI;
					elsif(AS = D1) then
						XLOWER(9) <= MDI;
					end if;
				elsif(DATACOUNT = 2) then
					if(AS = D0) then
						YLOWER(0) <= MDI;
					elsif(AS = D1) then
						YLOWER(1) <= MDI;
					elsif(AS = D2) then
						YLOWER(2) <= MDI;
					elsif(AS = D3) then
						YLOWER(3) <= MDI;
					elsif(AS = D4) then
						YLOWER(4) <= MDI;
					elsif(AS = D5) then
						YLOWER(5) <= MDI;
					elsif(AS = D6) then
						YLOWER(6) <= MDI;
					elsif(AS = D7) then
						YLOWER(7) <= MDI;
					end if;
				elsif(DATACOUNT = 3) then
					if(AS = D0) then
						YLOWER(8) <= MDI;
					elsif(AS = D1) then
						YLOWER(9) <= MDI;
					end if;
				elsif(DATACOUNT = 4) then
					if(AS = D0) then
						ZLOWER(0) <= MDI;
					elsif(AS = D1) then
						ZLOWER(1) <= MDI;
					elsif(AS = D2) then
						ZLOWER(2) <= MDI;
					elsif(AS = D3) then
						ZLOWER(3) <= MDI;
					elsif(AS = D4) then
						ZLOWER(4) <= MDI;
					elsif(AS = D5) then
						ZLOWER(5) <= MDI;
					elsif(AS = D6) then
						ZLOWER(6) <= MDI;
					elsif(AS = D7) then
						ZLOWER(7) <= MDI;
					end if;
				elsif(DATACOUNT = 5) then
					if(AS = D0) then
						ZLOWER(8) <= MDI;
					elsif(AS = D1) then
						ZLOWER(9) <= MDI;
					end if;
				end if;
				--end logic for getting data from accelerometer
			else
				--increment internal clock prescaler
				COUNT <= COUNT + 1;
			end if;
		end if;
	end process;

-- Create Next state logic. 
-- asserts CS then Read bit and MultiByte bit. Then proceeds to read the address of X0
-- after reading X0, read the following 6 data bytes to obtain X,Y,Z data. Then assert CS and start over
	NSL: process(AS) is
	begin
			case AS is
				when OFF => NS <= CSWAIT;
				when CSWAIT => NS <= READB;
				when READB => NS <= MULB;
				when MULB => NS <= A5;
				when A5 => NS <= A4;
				when A4 => NS <= A3;
				when A3 => NS <= A2;
				when A2 => NS <= A1;
				when A1 => NS <= A0;
				when A0 => NS <= D7;
				when D7 => NS <= D6;
				when D6 => NS <= D5;
				when D5 => NS <= D4;
				when D4 => NS <= D3;
				when D3 => NS <= D2;
				when D2 => NS <= D1;
				when D1 => NS <= D0;
				when D0 =>
					DATACOUNT <= DATACOUNT + 1;
					if(DATACOUNT = 6) then
						DATACOUNT <= 0;
						NS <= CSDIS;
					else
						NS <= D7;
					end if;
				when CSDIS => NS <= OFF;
				when others => NS <= OFF;
			end case;
	end process NSL;

	--assert output signals CS when needed
	with AS select
		CS <= '1' when CSWAIT|CSDIS, '0' when others;
	--Assert  READ signal, Multiple Byte signal, and address signals when appropriate
	with AS select
		MDO <= '1' when READB|MULB|A5|A4|A1, '0' when others;

	--set output accelerotmer values
	X <= XLOWER;
	Y <= YLOWER;
	Z <= ZLOWER;

end architecture BEHAV;




