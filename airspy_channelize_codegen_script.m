% AIRSPY_CHANNELIZE_CODEGEN_SCRIPT   Generate executable airspy_channelize from
%  airspy_channelize.
% 
% Script generated from project 'airspy_channelize.prj' on 24-Feb-2023.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('exe','ecoder',true);
cfg.TargetLang = 'C++';
cfg.GenCodeOnly = true;
cfg.GenerateExampleMain = 'DoNotGenerate';
cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;
cfg.RuntimeChecks = true;

%% Define argument types for entry-point 'airspy_channelize'.
ARGS = cell(1,1);
ARGS{1} = cell(1,1);
ARGS{1}{1} = coder.typeof(int32(0),[1 Inf],[0 1]);

%% Invoke MATLAB Coder.
codegen -config cfg airspy_channelize -args ARGS{1}

