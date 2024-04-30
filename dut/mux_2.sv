module mux_2 #(parameter BITS=8) (
    input  wire            i_ab_sw,   
    input  wire [BITS-1:0] i_a,   
    input  wire [BITS-1:0] i_b,   
    output wire [BITS-1:0] o_out       
);

assign o_out = i_ab_sw ? i_a : i_b;
    
endmodule
