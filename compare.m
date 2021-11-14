% import txt data used as input to C script
c_input = textread("data.txt", "%f");
c_input = c_input(2:end);

% zero pad the input for use in matlab
c_input_padded = zeros(2^ceil(log2(length(c_input))), 1);
for i=1:length(c_input)
    c_input_padded(i) = c_input(i);
end


% import txt data exported by C script
c_output_raw = textread("fftout.txt", "%s");
c_output = zeros(length(A));
for i=1:length(c_output)
    c_output = str2double(c_output_raw);
end

% plot for comparison
figure
plot(abs(c_output));

figure
plot(abs(fftshift(fft(c_input_padded, 64))));

