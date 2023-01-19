% airspy_channelize_CODEGEN_SCRIPT_EXE   Generate executable airspy_channelize
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
cfg = coder.config('exe','ecoder',false);
cfg.CustomInclude = [curr_dir,'/CustomMains'];
cfg.CustomSource  = [curr_dir,'/CustomMains/main.c'];
%cfg.GenCodeOnly = true;
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;

%% Define argument types for entry-point 'airspy_channelize'.
ARGS = cell(1,1);
ARGS{1} = cell(2,1);
ARGS{1}{1} = coder.typeof(0);
ARGS{1}{2} = coder.typeof(0);

%% Invoke MATLAB Coder.
cd(curr_dir)
tic
codegen -config cfg airspy_channelize -args ARGS{1}
toc
