% airspy_channelize_CODEGEN_SCRIPT_LIB   Generate executable airspy_channelize
%  from airspy_channelize.
% 
% Script generated from project 'airspy_channelize.prj' on 06-Jun-2022.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

curr_dir = pwd;
current_folder_name = curr_dir(find(curr_dir=='/',1,'last')+1:end);
if ~strcmp(current_folder_name,'airspy_channelize')
    error('This function must be run in the airspy_channelize root directory. Navigate to <repo location>/airspy_channelize and run again.')
end

%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('lib','ecoder',false);
cfg.CustomInclude = [curr_dir,'/CustomMains'];
cfg.CustomSource  = [curr_dir,'/CustomMains/main.c'];
cfg.GenCodeOnly = true;
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;

%% Define argument types for entry-point 'airspy_channelize'.
ARGS = cell(1,1);
ARGS{1} = cell(2,1);
ARGS{1}{1} = coder.typeof(0);
ARGS{1}{2} = coder.typeof(0);

%% Invoke MATLAB Coder.
%cd('/home/dasl/airspy_channelize');
tic
codegen -config cfg airspy_channelize -args ARGS{1}
toc
cd([curr_dir,'/codegen/lib/airspy_channelize'])
[makestatus,makecmdout] = system('make -f airspy_channelize_rtw.mk');
disp('Make complete.')
load buildInfo.mat
packNGo(buildInfo,'packType','flat','fileName','portairspy_channelize')
disp('Zip complete.')
cd(curr_dir)
[mkdirstatus, mkdircmdout] = system('mkdir ~/Desktop/portairspy_channelize');
[mvzipstatus, mvzipcmdout] = system('mv portairspy_channelize.zip ~/Desktop/portairspy_channelize/portairspy_channelize.zip');
disp('Zip transfer complete.')
cd('~/Desktop/portairspy_channelize')
[unzipstatus, unzipcmdout] = system('unzip portairspy_channelize');
disp('Unzip complete.')
[cp1status,cp1cmdout] = system('cp /usr/lib/x86_64-linux-gnu/libdl.so ~/Desktop/portairspy_channelize/libdl.so');
systemcopycommand = ['cp ',matlabroot,'/sys/os/glnxa64/libiomp5.so ~/Desktop/portairspy_channelize/libiomp5.so'];
[cp2status,cp2cmdout] = system(systemcopycommand);
[exprtstatus, exprtcmdout] = system('export LD_LIBRARY_PATH=~/Desktop/portairspy_channelize');
disp('Library transfers complete')
%Added -lm to deal with underfined reference to 'sin' error. Found solution
%at https://stackoverflow.com/questions/5005363/undefined-reference-to-sin
[cmplstatus, cmplcmdout] = system('gcc main.c *.a *.so -o airspy_channelize -lm');
if cmplstatus==0
    disp('Process complete. Executable generated.')
else
    disp(['Compile failed with output: ',cmplcmdout])
end

