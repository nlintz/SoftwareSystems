from ch01 import *

def run_simulation(*controllers):
	p = Buffer( 50, 10 )
	return [closed_loop( c, p, 1000 ) for c in controllers]

def rms_error(es):
	return numpy.sqrt(numpy.mean(numpy.array(es)**2))

def run_trial(num_trials, *controllers):
	errors = [0 for i in range(len(controllers))]

	for i in range(num_trials):
		simulation_results = run_simulation(*controllers)
		for error_i in range(len(errors)):
			errors[error_i] += rms_error(simulation_results[error_i][3]) #Errors are the third element in the tuple returned by closed_loop

	for i, error in enumerate(errors):
		errors[i] = error / 1.0 / num_trials

	return errors

# Tests print rms in the same order that controllers are passed in
def test_P_vs_PI():
	c_ki_non_zero = Controller(1.25, 0.01)
	c_ki_zero = Controller( 1.25, 0.00 )
	print run_trial(100, c_ki_zero, c_ki_non_zero)

def test_PI_vs_PID():
	pid_controller = PIDController(1.25, 0.01, 0.1) # PI Controller is better
	pi_controller = PIDController(1.25, 0.01, 0)
	print run_trial(10, pid_controller, pi_controller)

def test_maximize_RMS():
	pid_controller = PIDController(1.25, 0.01, 100) # PI Controller is better
	print run_trial(10, pid_controller)

if __name__ == "__main__":
	test_maximize_RMS()