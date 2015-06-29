package mobile.android.leds.hal.service;

public class LedHalService {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		LedHalService ledHalService = LedHalService.getInstance();
		ledHalService.setOn(0);
		ledHalService.setOff(1);
		ledHalService.setOn(2);
		ledHalService.setOff(3);
		
	}

	private static LedHalService ledHalService;
	public static LedHalService getInstance(){
		if(ledHalService ==null)
			return new LedHalService();
		else
			return ledHalService;
	}
	
	private LedHalService(){
		init();
	}
	
	public boolean init(){
		return _init();
	}
	
	public boolean setOn(int led){
		return _set_on(led);
	}
	
	public boolean setOff(int led){
		return _set_off(led);
	}
	
	private native boolean _init();
	private native boolean _set_on(int led);
	private native boolean _set_off(int led);
	
	static{
		System.load("/system/lib/led_hal_jni.so");
	}
}
