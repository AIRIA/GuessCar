package com.giant.jni;

import net.youmi.android.banner.AdSize;
import net.youmi.android.banner.AdView;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;

import com.giant.net.NetManager;

public class JniBrige {

	public native void exitGame();

	static public JniBrige _instance;
	public Activity context;
	private boolean showAds = false;

	public static Object getObject() {
		return getInstance();
	}

	public static JniBrige getInstance() {
		if (_instance == null) {
			_instance = new JniBrige();
		}
		return _instance;
	}

	public void init(Context context) {
		this.context = (Activity) context;
		try {
			String adsSetting = NetManager
					.sendHttpRequest("https://gist.githubusercontent.com/AIRIA/6f0906e11d40a6d1c0e0/raw");
			if (adsSetting == null) {
				return;
			}
			JSONObject setting = new JSONObject(adsSetting);
			showAds = setting.getBoolean(getVersion());
			if (showAds) {
				this.context.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						SpotManager.getInstance(JniBrige.this.context)
								.loadSpotAds();
					}
				});

			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public void showFeedBack(String params) {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				// FeedbackAgent agent = new FeedbackAgent(context);
				// agent.startFeedbackActivity();
				// agent.sync();
			}
		});

	}

	public void showBannerAd(String params) {
		Log.v("YouMi", "invoke show Banner Ad");
		context.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				if(!showAds)
					return;
				FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
						FrameLayout.LayoutParams.MATCH_PARENT,
						FrameLayout.LayoutParams.WRAP_CONTENT);

				layoutParams.gravity = Gravity.BOTTOM | Gravity.CENTER;
				AdView adView = new AdView(context, AdSize.FIT_SCREEN);
				context.addContentView(adView, layoutParams);
			}

		});
	}

	public void showSpotAd(String params) {
		Log.v("YouMi", "invoke show spot ad");
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (SpotManager.getInstance(context).checkLoadComplete()) {
					Log.v("Youmi", "invoke showspotads");
					SpotManager.getInstance(context).showSpotAds(context,
							new SpotDialogListener() {
								@Override
								public void onShowSuccess() {
									Log.i("Youmi", "onShowSuccess");
								}

								@Override
								public void onShowFailed() {
									Log.i("Youmi", "onShowFailed");
								}

								@Override
								public void onSpotClosed() {
									Log.e("sdkDemo", "closed");
								}
							});
				}

			}
		});
	}

	public String getVersion() {
		try {
			PackageManager manager = context.getPackageManager();
			PackageInfo info = manager.getPackageInfo(context.getPackageName(),
					0);
			String version = info.versionName;
			return version;
		} catch (Exception e) {
			e.printStackTrace();
			return "0";
		}
	}

}
