import pandas as pd
import numpy as np
from sqlalchemy import create_engine, text

df = pd.read_csv("instagram_usage_lifestyle.csv")

# Sample 1500 rows if necessary
if len(df) > 1500:
    df = df.sample(n=1500, random_state=42).reset_index(drop=True)

df.columns = df.columns.str.strip()
df = df.replace({"â€™": "'"}, regex=True)

bool_map = {"Yes": True, "No": False, "yes": True, "no": False}
bool_cols = ["has_children", "two_factor_auth_enabled", "biometric_login_used", "uses_premium_features"]
for col in bool_cols:
    if col in df.columns:
        df[col] = df[col].map(bool_map).fillna(False).astype(bool)

# Convert Dates
df["last_login_date"] = pd.to_datetime(df["last_login_date"], errors="coerce").dt.date

engine = create_engine("mysql+mysqlconnector://root:123456@localhost/socialmedia")

user_df = df[[
    "age", "gender", "urban_rural", "relationship_status", "has_children", "country"
]].copy()

# Insert and then get the IDs back to ensure mapping is 1:1
with engine.begin() as conn:
    user_df.to_sql("user", conn, if_exists="append", index=False)
    # Fetch the IDs of the rows we just inserted
    # Assuming this is a fresh or sequential insert, we get the last N ids
    query = text("SELECT userid FROM user ORDER BY userid DESC LIMIT :limit")
    result = conn.execute(query, {"limit": len(user_df)}).fetchall()
    # IDs are returned in descending order; reverse them to match df order
    new_ids = [r[0] for r in reversed(result)]
    df["userid"] = new_ids

# Mental Profile
df[["userid", "self_reported_happiness", "perceived_stress_score"]].to_sql(
    "mentalprofile", engine, if_exists="append", index=False
)

# Health Profile
health_df = df[["userid", "blood_pressure_systolic", "blood_pressure_diastolic", 
               "body_mass_index", "sleep_hours_per_night", "diet_quality"]].copy()
health_df.columns = ["userid", "systolicbp", "diastolicbp", "body_mass_index", "sleep_hours_per_night", "diet_quality"]
health_df.to_sql("healthprofile", engine, if_exists="append", index=False)

# Work Profile
df[["userid", "income_level", "employment_status", "weekly_work_hours"]].to_sql(
    "workprofile", engine, if_exists="append", index=False
)

# Lifestyle Profile
life_df = df[["userid", "travel_frequency_per_year", "books_read_per_year", 
              "social_events_per_month", "hobbies_count", "volunteer_hours_per_month"]].copy()
life_df.rename(columns={"travel_frequency_per_year": "travel_freq_per_year"}, inplace=True)
life_df.to_sql("lifestyleprofile", engine, if_exists="append", index=False)

# Prepare Account Data
account_df = pd.DataFrame({
    "userid": df["userid"],
    "follows_count": df["followers_count"], # Map your CSV col to schema col
    "following_count": df["following_count"],
    "user_premium": df["uses_premium_features"],
    "account_creation_date": pd.to_datetime(df["account_creation_year"], format='%Y', errors='coerce').dt.date,
    "last_login_date": df["last_login_date"],
    "average_session_length": df["average_session_length_minutes"],
    "linked_accounts_count": df["linked_accounts_count"],
    "subscription_status": df["subscription_status"],
    "user_engagement_score": df["user_engagement_score"],
    "notification_response_rate": df["notification_response_rate"],
    "preferred_content_theme": df["preferred_content_theme"],
    "content_type_preference": df["content_type_preference"],
    "sessions_per_day": df["sessions_per_day"]
})

with engine.begin() as conn:
    account_df.to_sql("account", conn, if_exists="append", index=False)
    # Fetch Account IDs for Security Settings mapping
    query = text("SELECT accountid FROM account ORDER BY accountid DESC LIMIT :limit")
    result = conn.execute(query, {"limit": len(account_df)}).fetchall()
    acc_ids = [r[0] for r in reversed(result)]
    df["accountid"] = acc_ids

# Security Settings
security_df = pd.DataFrame({
    "accountid": df["accountid"],
    "two_factor_auth_enabled": df["two_factor_auth_enabled"],
    "biometric_login_enabled": df["biometric_login_used"],
    "privacy_setting": df["privacy_setting_level"]
})
security_df.to_sql("securitysettings", engine, if_exists="append", index=False)

insta_df = df[[
    "userid", "posts_created_per_week", "reels_watched_per_day", "stories_viewed_per_day",
    "likes_given_per_day", "comments_written_per_day", "time_on_messages_per_day",
    "dms_sent_per_week", "dms_received_per_week", "daily_active_minutes_instagram",
    "ads_clicked_per_day", "ads_viewed_per_day", "time_on_reels_per_day",
    "time_on_explore_per_day", "time_on_feed_per_day"
]].copy()

insta_df.rename(columns={
    "comments_written_per_day": "comments_made_per_day",
    "time_on_messages_per_day": "time_on_message_per_day",
    "daily_active_minutes_instagram": "daily_active_minutes"
}, inplace=True)

insta_df.to_sql("instaactivity", engine, if_exists="append", index=False)

print(f"Successfully inserted {len(df)} records into the database.")