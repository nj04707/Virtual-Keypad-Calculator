module ex_interface
(
	input [7:0]data_from_exHW, 
	input [7:0]data_from_SW,
	output [7:0]data_to_exHW, 
	output [7:0]data_to_SW 
);

assign data_to_exHW = data_from_SW;
assign data_to_SW = data_from_exHW;


endmodule
