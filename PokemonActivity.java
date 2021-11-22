package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.telephony.CellIdentity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.squareup.picasso.Picasso;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;
import java.util.Set;

public class PokemonActivity extends AppCompatActivity implements View.OnClickListener{
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView flavorTextView;
    private String url;
    private RequestQueue requestQueue;
    private Button caught;
    private boolean isCatch;
    private ImageView pokeImageView;
    public static String NAME;
    public static int id;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        flavorTextView = findViewById(R.id.flavortext);
        caught = findViewById(R.id.button_catch);
        pokeImageView = findViewById(R.id.pokepic);
        NAME = getIntent().getStringExtra("name");

        caught.setOnClickListener(this);


        load();
        isCatch = loadPreferences();

        if (!isCatch) {
            caught.setText("Catch");
            isCatch = false;

        }
        else {
            caught.setText("Release");
            isCatch = true;
        }
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {

            @Override
            public void onResponse(JSONObject response) {
                try {

                    id = response.getInt("id");
                    String descurl = String.format("https://pokeapi.co/api/v2/pokemon-species/%d/",id);
                    final JsonObjectRequest request1 = new JsonObjectRequest(Request.Method.GET, descurl, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                JSONArray flavorEntries = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < flavorEntries.length(); i++) {

                                    JSONObject description = flavorEntries.getJSONObject(i);

                                    String lang = description.getJSONObject("language").getString("name");

                                    if(lang.equals("en")){
                                       String flavorText = description.getString("flavor_text");
                                       flavorTextView.setText(flavorText);
                                       break;
                                    }

                                }

                            } catch (JSONException e) {
                                Log.e("cs50", "Json error", e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "flavorText list error", error);
                        }
                    });
                    requestQueue.add(request1);

                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));
                    String imgUrl = response.getJSONObject("sprites").getString("front_default");
                    new DownloadSpriteTask().execute(imgUrl);
                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        } else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });


        requestQueue.add(request);
    }

   @Override
    public void onClick(View view) {


        if (!isCatch) {
           caught.setText("Release");
            isCatch = true;
            Toast.makeText(this, "You caught it!", Toast.LENGTH_SHORT).show();
        }
        else {
           caught.setText("Catch");
            isCatch = false;
            Toast.makeText(this, "Farewell!", Toast.LENGTH_SHORT).show();
        }

        savePreferences();
    }
    private void savePreferences() {
        SharedPreferences preferences = getSharedPreferences(NAME, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = preferences.edit();
        editor.putBoolean(NAME, isCatch);
        editor.apply();
    }

   public boolean loadPreferences() {
        SharedPreferences preferences = getSharedPreferences(NAME, Context.MODE_PRIVATE);
        boolean isCaught = preferences.getBoolean(NAME, isCatch);
        return isCaught;
    }

  private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
      @Override
      protected Bitmap doInBackground(String... strings) {
          try {
              URL url = new URL(strings[0]);
              return BitmapFactory.decodeStream(url.openStream());
          } catch (IOException e) {
              Log.e("cs50", "Download sprite error", e);
              return null;
          }
      }
      @Override
      protected void onPostExecute (Bitmap bitmap) {
          pokeImageView.setImageBitmap(bitmap);
      }

  }
}


